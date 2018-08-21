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
