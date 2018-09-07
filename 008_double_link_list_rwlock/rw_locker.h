#ifndef _RW_LOCKER_H
#define _RW_LOCKER_H

#include "locker.h"

typedef struct _RwLocker RwLocker;

RwLocker *rw_locker_create(Locker *w_locker, Locker *r_locker);
Ret rw_locker_wlock(RwLocker *thiz);
Ret rw_locker_rlock(RwLocker *thiz);
Ret rw_locker_unlock(RwLocker *thiz);
void rw_locker_destroy(RwLocker *thiz);

#endif /* _RW_LOCKER_H */
