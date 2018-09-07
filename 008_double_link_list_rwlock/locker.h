#ifndef _LOCKER_H
#define _LOCKER_H

#include "typedefs.h"

DECLS_BEGIN

typedef struct _Locker Locker;
typedef Ret (*LockerLockFunc)(Locker *thiz);
typedef Ret (*LockerUnlockFunc)(Locker *thiz);
typedef void (*LockerDestroyFunc)(Locker *thiz);

struct _Locker {
    LockerLockFunc lock;
    LockerUnlockFunc unlock;
    LockerDestroyFunc destroy;
    char priv[0];
};

static inline Ret locker_lock(Locker *thiz)
{
    return_val_if_fail(thiz != NULL && thiz->lock != NULL, RET_INVALID_PARAMS);
    return thiz->lock(thiz);
}

static inline Ret locker_unlock(Locker *thiz)
{
    return_val_if_fail(thiz != NULL && thiz->unlock != NULL, RET_INVALID_PARAMS);
    return thiz->unlock(thiz);
}

static inline void locker_destroy(Locker *thiz)
{
    return_if_fail(thiz != NULL && thiz->lock != NULL);
    thiz->destroy(thiz);
}

DECLS_END

#endif /* _LOCKER_H */
