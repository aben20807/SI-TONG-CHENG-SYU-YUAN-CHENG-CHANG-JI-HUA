#ifndef _LOCKER_H
#define _LOCKER_H

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

static inline Ret locker_lock(Lock)

#endif
