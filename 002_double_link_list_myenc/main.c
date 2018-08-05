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
    return 0;
}
