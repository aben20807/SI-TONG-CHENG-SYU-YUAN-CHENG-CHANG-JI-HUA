#include <stdio.h>
#include <pthread.h>

#define TIMES 100000
#define ATOMIC_SMP_LOCK "lock ; "

typedef struct {
    volatile int counter;
} atomic_t;

static inline void atomic_inc(atomic_t *v)
{
    __asm__ __volatile__ (
        ATOMIC_SMP_LOCK "incl %0"
        :"=m" (v->counter)
        :"m" (v->counter)
    );
}

static inline void atomic_dec(atomic_t *v)
{
    __asm__ __volatile__ (
        ATOMIC_SMP_LOCK "decl %0"
        :"=m" (v->counter)
        :"m" (v->counter)
    );
}

void *thread_inc(void *param)
{
    atomic_t *n = (atomic_t *)param;
    for (int i = 0; i < TIMES; i++) {
        atomic_inc(n);
    }
    return NULL;
}

void *thread_dec(void *param)
{
    atomic_t *n = (atomic_t *)param;
    for (int i = 0; i < TIMES; i++) {
        atomic_dec(n);
    }
    return NULL;
}

int main(void)
{
    printf("atomic:\n");
    atomic_t count = { .counter = 0};
    pthread_t inc_tid = 0;
    pthread_t dec_tid = 0;

    pthread_create(&inc_tid, NULL, thread_inc, &count);
    pthread_create(&dec_tid, NULL, thread_dec, &count);

    pthread_join(inc_tid, NULL);
    pthread_join(dec_tid, NULL);

    printf("%d\n", count.counter);
    return 0;
}
