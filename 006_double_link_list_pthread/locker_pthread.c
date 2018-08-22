#include <stdlib.h>
#include <pthread.h>
#include "locker_pthread.h"

typedef struct _PrivInfo PrivInfo;
struct _PrivInfo {
    pthread_mutex_t mutex;
};

Locker *locker_pthread_create(void)
{
    Locker *ret = (Locker *)malloc(sizeof(Locker) + sizeof(PrivInfo));
    if (ret != NULL) {
        PrivInfo *priv = (PrivInfo *)ret->priv;
        ret->lock = locker_pthread_lock;
        ret->unlock = locker_pthread_unlock;
        ret->destroy = locker_pthread_destroy;
        pthread_mutex_init(&(priv->mutex), NULL);
    }
    return ret;
}

static Ret locker_pthread_lock(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    int ret = pthread_mutex_lock(&priv->mutex);
    return (ret == 0)? OK: ERR;
}

static Ret locker_pthread_unlock(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    int ret = pthread_mutex_unlock(&priv->mutex);
    return (ret == 0)? OK: ERR;
}

static void locker_pthread_destroy(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;
    int ret = pthread_mutex_destroy(&priv->mutex);
    free(thiz);
}
