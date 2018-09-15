#include <stdio.h>
#include <pthread.h>
#include "locker_pthread.h"

#define TIMES 100000

typedef struct {
    int counter;
    Locker *locker;
} locked_t;

static void locked_lock(locked_t *thiz)
{
    if (thiz->locker != NULL) {
        locker_lock(thiz->locker);
    }
}

static void locked_unlock(locked_t *thiz)
{
    if (thiz->locker != NULL) {
        locker_unlock(thiz->locker);
    }
}

static void locked_destroy(locked_t *thiz)
{
    if (thiz->locker != NULL) {
        locker_unlock(thiz->locker);
        locker_destroy(thiz->locker);
    }
}

static inline void inc(locked_t *thiz)
{
    locked_lock(thiz);
    (thiz->counter)++;
    locked_unlock(thiz);
}

static inline void dec(locked_t *thiz)
{
    locked_lock(thiz);
    (thiz->counter)--;
    locked_unlock(thiz);
}

void *thread_inc(void *param)
{
    locked_t *n = (locked_t *)param;
    for (int i = 0; i < TIMES; i++) {
        inc(n);
    }
    return NULL;
}

void *thread_dec(void *param)
{
    locked_t *n = (locked_t *)param;
    for (int i = 0; i < TIMES; i++) {
        dec(n);
    }
    return NULL;
}

int main(void)
{
    printf("locked:\n");
    locked_t count = {
        .counter = 0,
        .locker = locker_pthread_create(),
    };
    pthread_t inc_tid = 0;
    pthread_t dec_tid = 0;

    pthread_create(&inc_tid, NULL, thread_inc, &count);
    pthread_create(&dec_tid, NULL, thread_dec, &count);

    pthread_join(inc_tid, NULL);
    pthread_join(dec_tid, NULL);

    printf("%d\n", count.counter);
    return 0;
}
