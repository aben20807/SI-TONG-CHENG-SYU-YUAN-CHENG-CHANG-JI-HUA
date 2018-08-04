#include <stdlib.h>
#include "dlist.h"

#define NULL_CHECK(ptr) \
    do { \
        if (ptr == NULL) ERR; \
    } while(0)
#define INDEX_CHECK(list, index) \
    do { \
        if (index >= list->size) ERR; \
    } while(0)

typedef struct _Node {
    void *data;
    struct _Node *pre;
    struct _Node *nxt;
} Node;

struct _DList {
    int size;
    Node *head;
    Node *tail;
};

DList *dlist_create(void)
{
    DList *ret = malloc(sizeof(DList));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

Status dlist_insert(DList *this, size_t index, void *data)
{
    NULL_CHECK(this);
    int cnt = 0;
    Node *cur = this->head;
    return ERR;
}

Status dlist_prepend(DList *this, void *data);
Status dlist_append(DList *this, void *data);
Status dlist_delete(DList *this, size_t index);
Status dlist_get_by_index(DList *this, size_t index, void **data);
Status dlist_set_by_index(DList *this, size_t index, void *data);
size_t dlist_size(DList *this);

static Node *node_create(void *data)
{
    Node *ret = malloc(sizeof(Node));
    ret->data = data;
    ret->pre = NULL;
    ret->nxt = NULL;
    return ret;
}

static Node *node_at(DList *this, const int index)
{
    NULL_CHECK(this);
    INDEX_CHECK(this, index);
    Node *itr = this->head;
    int cnt = 0;
    while (itr != NULL) {
        if (cnt++ == index) {
            return itr;
        }
        itr = itr->nxt;
    }
    return NULL;
}
