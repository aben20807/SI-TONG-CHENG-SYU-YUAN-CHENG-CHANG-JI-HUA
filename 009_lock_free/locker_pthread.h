#ifndef LOCKER_PTHREAD_H
#define LOCKER_PTHREAD_H

#include <stdlib.h>
#include <pthread.h>
#include "locker.h"

Locker *locker_pthread_create(void);

#endif /* LOCKER_PTHREAD_H */
