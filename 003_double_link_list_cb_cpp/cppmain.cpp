#include <cstdio>
#include "dlist.h"
using namespace std;

DListRet print_int(void *data, bool is_first)
{
    if (is_first) {
        printf("%d", *(int *)data);
    } else {
        printf(" - %d", *(int *)data);
    }
}

DListRet sum_cb(void *ctx, void *data, bool is_first)
{
    long long *result = (long long *)ctx;
    *result += *(int *)data;
    return OK;
}

DListRet max_cb(void *ctx, void *data, bool is_first)
{
    int *result = (int *)ctx;
    if (is_first) {
        *result = *(int *)data;
    } else {
        *result = (*result > *(int *)data)? *result: *(int *)data;
    }
    return OK;
}


int main()
{
    printf("OuO\n");
    DList *d = dlist_create();
    dlist_print(d, print_int);

    int data1 = 1;
    dlist_prepend(d, &data1);
    dlist_print(d, print_int);

    int data2 = 2;
    dlist_prepend(d, &data2);
    dlist_print(d, print_int);

    int data3 = 3;
    dlist_append(d, &data3);
    dlist_print(d, print_int);

    int data4 = 4;
    dlist_append(d, &data4);
    dlist_print(d, print_int);

    int data5 = 5;
    dlist_insert(d, 3, &data5);
    dlist_print(d, print_int);

    int data6 = 6;
    dlist_insert(d, 3, &data6);
    dlist_print(d, print_int);

    long long sum = 0;
    dlist_foreach(d, sum_cb, &sum);
    printf("sum: %lld\n", sum);

    int max;
    dlist_foreach(d, max_cb, &max);
    printf("max: %d\n", max);

    dlist_delete(d, 2);
    dlist_print(d, print_int);

    dlist_delete(d, 1);
    dlist_print(d, print_int);

    dlist_delete(d, 11);
    dlist_print(d, print_int);

    dlist_delete(d, 0);
    dlist_print(d, print_int);

    void *data7;
    dlist_get_by_index(d, 0, &data7);
    printf("%d\n", *(int *)data7);

    dlist_get_by_index(d, 2, &data7);
    printf("%d\n", *(int *)data7);

    int data8 = 8;
    dlist_set_by_index(d, 0, &data8);
    dlist_print(d, print_int);

    dlist_set_by_index(d, 2, &data8);
    dlist_print(d, print_int);

    dlist_destroy(d);
    return 0;
}
