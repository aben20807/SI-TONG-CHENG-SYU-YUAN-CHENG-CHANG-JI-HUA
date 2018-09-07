#include "rw_locker.h"

typedef enum _RwLockerMode {
    RW_LOCKER_NONE,
    RW_LOCKER_W,
    RW_LOCKER_R,
} RwLockerMode;

struct _RwLocker {
    int readers;
    RwLockerMode mode;
    Locker *w_locker;
    Locker *r_locker;
};

RwLocker *rw_locker_create(Locker *w_locker, Locker *r_locker)
{
    return_val_if_fail(w_locker != NULL && r_locker != NULL, NULL);
    RwLocker *ret = (RwLocker *)malloc(sizeof(RwLocker));
    if (ret != NULL) {
        ret->readers = 0;
        ret->mode = RW_LOCKER_NONE;
        ret->w_locker = w_locker;
        ret->r_locker = r_locker;
    }
    return ret;
}

Ret rw_locker_wlock(RwLocker *thiz)
{
    Ret ret = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
    if ((ret = locker_lock(thiz->w_locker)) == RET_OK) {
        thiz->mode = RW_LOCKER_W;
    }
    return ret;
}

Ret rw_locker_rlock(RwLocker *thiz)
{
    Ret ret = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
    if ((ret = locker_lock(thiz->r_locker)) == RET_OK) {
        thiz->readers++;
        if (thiz->readers == 1) {
            ret = locker_lock(thiz->w_locker);
            thiz->mode = RW_LOCKER_R;
        }
        locker_unlock(thiz->r_locker);
    }
    return ret;
}

Ret rw_locker_unlock(RwLocker *thiz)
{
    Ret ret = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
    if (thiz->mode == RW_LOCKER_W) {
        thiz->mode = RW_LOCKER_NONE;
        ret = locker_unlock(thiz->w_locker);
    } else {
        return_val_if_fail(thiz->mode == RW_LOCKER_R, RET_FAIL);
        if ((ret = locker_lock(thiz->r_locker)) == RET_OK) {
            thiz->readers--;
            if (thiz->readers == 0) {
                thiz->mode = RW_LOCKER_NONE;
                ret = locker_unlock(thiz->w_locker);
            }
            locker_unlock(thiz->r_locker);
        }
    }
    return ret;
}

void rw_locker_destroy(RwLocker *thiz)
{
    if (thiz != NULL) {
        locker_destroy(thiz->w_locker);
        locker_destroy(thiz->r_locker);
        free(thiz);
    }
}
