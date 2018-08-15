#include <cstdio>
#include "dlist.h"
using namespace std;

DListRet print_int(void *ctx, void *data, bool is_first)
{
    if (is_first) {
        printf("%d", *(int *)data);
    } else {
        printf(" - %d", *(int *)data);
    }
    return OK;
}

void print(DList *thiz) {
    printf("size: %d, list: ", dlist_size(thiz));
    dlist_foreach(thiz, print_int, NULL);
    printf("\n");
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

int main(){

    printf("OuO\n");
    DList *d = dlist_create();
    print(d);

    int data1 = 1;
    dlist_prepend(d, &data1);
    print(d);

    int data2 = 2;
    dlist_prepend(d, &data2);
    print(d);

    int data3 = 3;
    dlist_append(d, &data3);
    print(d);

    int data4 = 4;
    dlist_append(d, &data4);
    print(d);

    int data5 = 5;
    dlist_insert(d, 3, &data5);
    print(d);

    int data6 = 6;
    dlist_insert(d, 3, &data6);
    print(d);

    long long sum = 0;
    dlist_foreach(d, sum_cb, &sum);
    printf("sum: %lld\n", sum);

    int mmax;
    dlist_foreach(d, max_cb, &mmax);
    printf("max: %d\n", mmax);

    dlist_delete(d, 2);
    print(d);

    dlist_delete(d, 1);
    print(d);

    dlist_delete(d, 11);
    print(d);

    dlist_delete(d, 0);
    print(d);

    void *data7;
    dlist_get_by_index(d, 0, &data7);
    printf("%d\n", *(int *)data7);

    dlist_get_by_index(d, 2, &data7);
    printf("%d\n", *(int *)data7);

    int data8 = 8;
    dlist_set_by_index(d, 0, &data8);
    print(d);

    dlist_set_by_index(d, 2, &data8);
    print(d);

    dlist_destroy(d);
    return 0;
}
