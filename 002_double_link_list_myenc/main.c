#include <stdio.h>
#include "dlist.h"

int main(int argc, char *argv[]){

    printf("OuO\n");
    DList *d = dlist_create();
    dlist_print(d);

    int data1 = 1;
    dlist_prepend(d, &data1);
    dlist_print(d);

    int data2 = 2;
    dlist_prepend(d, &data2);
    dlist_print(d);

    int data3 = 3;
    dlist_append(d, &data3);
    dlist_print(d);

    int data4 = 4;
    dlist_append(d, &data4);
    dlist_print(d);

    int data5 = 5;
    dlist_insert(d, 3, &data5);
    dlist_print(d);

    int data6 = 6;
    dlist_insert(d, 3, &data6);
    dlist_print(d);

    dlist_delete(d, 2);
    dlist_print(d);

    dlist_delete(d, 1);
    dlist_print(d);

    dlist_delete(d, 11);
    dlist_print(d);

    dlist_delete(d, 0);
    dlist_print(d);

    void *data7;
    dlist_get_by_index(d, 0, &data7);
    printf("%d\n", *(int *)data7);

    dlist_get_by_index(d, 2, &data7);
    printf("%d\n", *(int *)data7);

    int data8 = 8;
    dlist_set_by_index(d, 0, &data8);
    dlist_print(d);

    dlist_set_by_index(d, 2, &data8);
    dlist_print(d);
    return 0;
}
