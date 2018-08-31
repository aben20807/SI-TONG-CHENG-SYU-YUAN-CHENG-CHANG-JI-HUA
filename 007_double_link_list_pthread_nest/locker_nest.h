#ifndef _LOCKER_NEST
#define _LOCKER_NEST

#include <stdlib.h>
#include "locker.h"

DECLS_BEGIN

typedef int (*TaskSelfFunc)(void);
Locker *locker_nest_create(Locker *real_locker, TaskSelfFunc task_self);

DECLS_END

#endif /* _LOCKER_NEST */
