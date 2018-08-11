#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

typedef struct _Node {
    void *data;
    struct _Node *pre;
    struct _Node *nxt;
} Node;

struct _DList {
    size_t size;
    Node *head;
    Node *tail;
};

static Node *node_create(void *data)
{
    Node *ret = malloc(sizeof(Node));
    ret->data = data;
    ret->pre = NULL;
    ret->nxt = NULL;
    return ret;
}

static Node *node_at(DList *thiz, const int index)
{
    if (thiz == NULL || 0 > index || index >= thiz->size) {
        return NULL;
    }
    Node *itr = thiz->head;
    int cnt = 0;
    while (itr != NULL) {
        if (cnt++ == index) {
            return itr;
        }
        itr = itr->nxt;
    }
    return NULL;
}

DList *dlist_create(void)
{
    DList *ret = malloc(sizeof(DList));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

Status dlist_insert(DList *thiz, size_t index, void *data)
{
    Node *new = node_create(data);
    if (thiz == NULL || data == NULL || new == NULL) {
        return ERR;
    }
    if (index == 0) {
        if (thiz->head == NULL) {
            thiz->head = new;
            thiz->tail = thiz->head;
        } else {
            thiz->head->pre = new;
            new->nxt = thiz->head;
            thiz->head = new;
        }
        thiz->size++;
        return OK;
    } else if (index == thiz->size) {
        if (thiz->tail == NULL) {
            thiz->tail = new;
            thiz->head = thiz->head;
        } else {
            thiz->tail->nxt = new;
            new->pre = thiz->tail;
            thiz->tail = new;
        }
        thiz->size++;
        return OK;
    } else if (0 < index && index < thiz->size) {
        Node *target = node_at(thiz, index);
        if (target != NULL) {
            target->pre->nxt = new;
            new->pre = target->pre;
            new->nxt = target;
            target->pre = new;
            thiz->size++;
            return OK;
        }
    } else {
        return ERR;
    }
}

Status dlist_prepend(DList *thiz, void *data)
{
    return dlist_insert(thiz, 0, data);
}

Status dlist_append(DList *thiz, void *data)
{
    return dlist_insert(thiz, thiz->size, data);
}

Status dlist_delete(DList *thiz, size_t index)
{
    if (thiz == NULL) {
        return ERR;
    }
    Node *target = node_at(thiz, index);
    if (target != NULL) {
        if (target->pre == NULL) {
            target->nxt->pre = NULL;
            thiz->head = target->nxt;
        } else if (target->nxt == NULL) {
            target->pre->nxt = NULL;
            thiz->tail = target->pre;
        } else {
            Node ret = *(target);
            target->nxt->pre = target->pre;
            target->pre->nxt = target->nxt;
        }
        free(target);
        target = NULL;
        thiz->size--;
        return OK;
    }
    return ERR;
}

Status dlist_get_by_index(DList *thiz, size_t index, void **data)
{
    if (thiz == NULL) {
        return ERR;
    }
    Node *target = node_at(thiz, index);
    if (target != NULL) {
        *data = target->data;
        return OK;
    }
    return ERR;
}

Status dlist_set_by_index(DList *thiz, size_t index, void *data)
{
    if (thiz == NULL) {
        return ERR;
    }
    Node *target = node_at(thiz, index);
    if (target != NULL) {
        target->data = data;
        return OK;
    }
    return ERR;
}

size_t dlist_size(const DList *thiz)
{
    return thiz->size;
}

void dlist_print(const DList *thiz) {
    if (thiz == NULL) {
        return;
    }
    printf("size: %d, list: ", thiz->size);
    Node *cur = thiz->head;
    if (cur != NULL) {
        printf("%d", *((int *)(cur->data)));
        cur = cur->nxt;
    }
    while (cur != NULL) {
        printf(" - %d", *((int *)(cur->data)));
        cur = cur->nxt;
    }
    printf("\n");
}