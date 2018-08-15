#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dlist.h"

DListRet str_print(void *ctx, void *data, bool is_first)
{
    if (is_first) {
        printf("%s", (char *)data);
    } else {
        printf(" %s", (char *)data);
    }
    return OK;
}

void print(DList *thiz) {
    printf("size: %d, list: ", dlist_size(thiz));
    dlist_foreach(thiz, str_print, NULL);
    printf("\n");
}

DListRet str_toupper(void *ctx, void *data, bool is_first)
{
    char *p = (char *)data;
    if (p != NULL) {
        while (*p != '\0') {
            if (islower(*p)) {
                *p = toupper(*p);
            }
            p++;
        }
    }
}

int main(int argc, char *argv[]){

    DList *d = dlist_create();
    dlist_append(d, strdup("It"));
    dlist_append(d, strdup("is"));
    dlist_append(d, strdup("OK"));
    dlist_append(d, strdup("!"));
    print(d);

    dlist_foreach(d, str_toupper, NULL);
    print(d);

    dlist_destroy(d);
    return 0;
}
