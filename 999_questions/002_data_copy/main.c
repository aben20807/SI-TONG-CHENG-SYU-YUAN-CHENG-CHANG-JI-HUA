#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    int a = 3;
    void *ptr1 = &a;
    printf("1: %d\n", *(int *)ptr1); // 3

    void *ptr2 = strdup(ptr1);
    printf("2: %d\n", *(int *)ptr2); // ???

    char *s = "string";
    void *ptr3 = strdup(s);
    printf("3: %s\n", ptr3); // string

    void *ptr4 = malloc(sizeof(*ptr1));
    memcpy(ptr4, ptr1, sizeof(*ptr1));
    printf("4: %d\n", *(int *)ptr4); // ???

    void *ptr5 = malloc(sizeof(*(int *)ptr1));
    memcpy(ptr5, ptr1, sizeof(*(int *)ptr1));
    printf("5: %d\n", *(int *)ptr5); // 3

    // 8
    printf("%ld, %ld, %ld\n", sizeof(ptr1), sizeof(&a), sizeof(void *));

    // 4
    printf("%ld, %ld, %ld\n", sizeof(*(int *)ptr1), sizeof(a), sizeof(int));

    // 1
    printf("%ld\n", sizeof(*ptr1));
    return 0;
}
