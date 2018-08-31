#include "locker_nest.h"

typedef struct _PrivInfo {
    int owner;
    int refcnt;
    Locker *real_locker;
    TaskSelfFunc task_self;
} PrivInfo;

static Ret locker_nest_lock(Locker *thiz)
{
    Ret ret = RET_OK;
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    if (priv->owner == priv->task_self()) {
        priv->refcnt++;
    } else {
        if ((ret = locker_lock(priv->real_locker)) == RET_OK) {
            priv->refcnt = 1;
            priv->owner = priv->task_self();
        }
    }
    return ret;
}

static Ret locker_nest_unlock(Locker *thiz)
{
    Ret ret = RET_OK;
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    return_val_if_fail(priv->owner == priv->task_self(), RET_FAIL);

    priv->refcnt--;
    if (priv->refcnt == 0) {
        priv->owner = 0;
        ret = locker_unlock(priv->real_locker);
    }
    return ret;
}

static void locker_nest_destroy(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    priv->owner = 0;
    priv->refcnt = 0;
    locker_destroy(priv->real_locker);
    free(thiz);
}

Locker *locker_nest_create(Locker *real_locker, TaskSelfFunc task_self)
{
    return_val_if_fail(real_locker != NULL && task_self != NULL, NULL);
    Locker *ret = (Locker *)malloc(sizeof(Locker) + sizeof(PrivInfo));
    if (ret != NULL) {
        PrivInfo *priv = (PrivInfo *)ret->priv;
        priv->owner = 0;
        priv->refcnt = 0;
        priv->real_locker = real_locker;
        priv->task_self = task_self;

        ret->lock = locker_nest_lock;
        ret->unlock = locker_nest_unlock;
        ret->destroy = locker_nest_destroy;
    }
    return ret;
}
