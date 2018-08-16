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
    if (ret != NULL) {
        ret->data = data;
        ret->pre = NULL;
        ret->nxt = NULL;
    }
    return ret;
}

static void node_destroy(Node **node)
{
    if (*node != NULL) {
        (*node)->pre = NULL;
        (*node)->nxt = NULL;
        free(*node);
        *node = NULL;
    }
}

static Node *node_at(DList *thiz, const int index)
{
    return_val_if_fail(thiz != NULL && 0 <= index && index < thiz->size, NULL);
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

void dlist_destroy(DList* thiz)
{
    return_if_fail(thiz != NULL);
    Node *itr = thiz->head;
    Node *next = NULL;
    while (itr != NULL) {
        next = itr->nxt;
        node_destroy(&itr);
        itr = next;
    }
}

DListRet dlist_insert(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL && data != NULL, ERR);
    Node *new = node_create(data);
    return_val_if_fail(new != NULL, ERR);
    if (index == 0 && thiz->size == 0) {
        thiz->head = new;
        thiz->tail = new;
        thiz->size++;
        return OK;
    }
    if (index == 0) {
        thiz->head->pre = new;
        new->nxt = thiz->head;
        thiz->head = new;
        thiz->size++;
        return OK;
    }
    if (index == thiz->size) {
        thiz->tail->nxt = new;
        new->pre = thiz->tail;
        thiz->tail = new;
        thiz->size++;
        return OK;
    }
    if (0 < index && index < thiz->size) {
        Node *target = node_at(thiz, index);
        if (target != NULL) {
            target->pre->nxt = new;
            new->pre = target->pre;
            new->nxt = target;
            target->pre = new;
            thiz->size++;
            return OK;
        }
    }
    node_destroy(&new);
    return ERR;
}

DListRet dlist_prepend(DList *thiz, void *data)
{
    return dlist_insert(thiz, 0, data);
}

DListRet dlist_append(DList *thiz, void *data)
{
    return dlist_insert(thiz, thiz->size, data);
}

DListRet dlist_delete(DList *thiz, size_t index)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *target = node_at(thiz, index);
    if (target != NULL) {
        if (target->pre == NULL) {
            target->nxt->pre = NULL;
            thiz->head = target->nxt;
        } else if (target->nxt == NULL) {
            target->pre->nxt = NULL;
            thiz->tail = target->pre;
        } else {
            target->nxt->pre = target->pre;
            target->pre->nxt = target->nxt;
        }
        node_destroy(&target);
        thiz->size--;
        return OK;
    }
    return ERR;
}

DListRet dlist_get_by_index(DList *thiz, size_t index, void **data)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *target = node_at(thiz, index);
    if (target != NULL) {
        *data = target->data;
        return OK;
    }
    return ERR;
}

DListRet dlist_set_by_index(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL, ERR);
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

DListRet dlist_foreach(DList *thiz, DListVisitFunc visit, void *ctx)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *itr = thiz->head;
    if (itr != NULL) {
        visit(ctx, itr->data, true);
        itr = itr->nxt;
    }
    while (itr != NULL) {
        visit(ctx, itr->data, false);
        itr = itr->nxt;
    }
    return OK;
}

#ifdef DLIST_TEST

#include <assert.h>

int main(){

    return 0;
}

#endif
