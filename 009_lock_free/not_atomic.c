#include <stdio.h>
#include <pthread.h>

#define TIMES int _i = 0; _i < 100000; _i++

void *thread_inc(void *count)
{
    for (TIMES) {
        (*(int *)count)++;
    }
    return NULL;
}

void *thread_dec(void *count)
{
    for (TIMES) {
        (*(int *)count)--;
    }
    return NULL;
}

int main(void){

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
