#ifndef _LOCKER_H
#define _LOCKER_H

#include "typedefs.h"

DECLS_BEGIN

typedef Ret (*LockerLockFunc)(Locker *thiz);
typedef Ret (*LockerUnlockFunc)(Locker *thiz);
typedef void (*LockerDestroyFunc)(Locker *thiz);

typedef struct _Locker Locker;
struct _Locker {
    LockerLockFunc lock;
    LockerUnlockFunc unlock;
    LockerDestroyFunc destroy;
    char priv[0];
}

static inline Ret locker_lock(Locker *thiz)
{
    return_val_if_fail(thiz != NULL && thiz->lock != NULL, ERR);
    return thiz->lock(thiz);
}

static inline Ret locker_unlock(Locker *thiz)
{
    return_val_if_fail(thiz != NULL && thiz->unlock != NULL, ERR);
    return thiz->unlock(thiz);
}

static inline void locker_destroy(Locker *thiz)
{
    return_val_if_fail(thiz != NULL && thiz->lock != NULL, ERR);
    thiz->destroy(thiz);
    return;
}

DECLS_END

#endif /* _LOCKER_H */
