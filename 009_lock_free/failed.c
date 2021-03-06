#include <stdio.h>
#include <pthread.h>

#define TIMES 1000000

static inline void inc(int *n)
{
    (*n)++;
}

static inline void dec(int *n)
{
    (*n)--;
}

void *thread_inc(void *param)
{
    int *n = (int *)param;
    for (int i = 0; i < TIMES; i++) {
        inc(n);
    }
    return NULL;
}

void *thread_dec(void *param)
{
    int *n = (int *)param;
    for (int i = 0; i < TIMES; i++) {
        dec(n);
    }
    return NULL;
}

int main(void)
{
    printf("failed:\n");
    int count = 0;
    pthread_t inc_tid = 0;
    pthread_t dec_tid = 0;

    pthread_create(&inc_tid, NULL, thread_inc, &count);
    pthread_create(&dec_tid, NULL, thread_dec, &count);

    pthread_join(inc_tid, NULL);
    pthread_join(dec_tid, NULL);

    printf("%d\n", count);
    return 0;
}
