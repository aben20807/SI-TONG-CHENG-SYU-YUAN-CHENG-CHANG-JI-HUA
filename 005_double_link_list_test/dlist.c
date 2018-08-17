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
    Node *ret = calloc(1, sizeof(Node));
    if (ret != NULL) {
        ret->data = data;
        ret->pre = NULL;
        ret->nxt = NULL;
    }
    return ret;
}

static void node_destroy(Node *node)
{
    if (node != NULL) {
        (node)->pre = NULL;
        (node)->nxt = NULL;
        free(node);
    }
}

static Node *node_at(DList *thiz, const int index)
{
    return_val_if_fail(thiz != NULL && 0 <= index && index < thiz->size, NULL);
    Node *itr = thiz->head->nxt;
    int cnt = 0;
    while (itr != thiz->tail) {
        if (cnt++ == index) {
            return itr;
        }
        itr = itr->nxt;
    }
    return NULL;
}

DList *dlist_create(void)
{
    DList *ret = calloc(1, sizeof(DList));
    ret->size = 0;
    ret->head = calloc(1, sizeof(Node));
    ret->tail = calloc(1, sizeof(Node));
    ret->head->nxt = ret->tail;
    ret->tail->pre = ret->head;
    return ret;
}

void dlist_destroy(DList* thiz)
{
    return_if_fail(thiz != NULL);
    Node *itr = thiz->head->nxt;
    Node *next = NULL;
    while (itr != thiz->tail) {
        next = itr->nxt;
        node_destroy(itr);
        itr = next;
    }
    free(thiz);
}

DListRet dlist_insert(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL && data != NULL, ERR);
    Node *new = node_create(data);
    return_val_if_fail(new != NULL, ERR);
    Node *target = NULL;
    if (index == thiz->size) {
        target = thiz->tail;
    } else if (0 <= index && index < thiz->size) {
        target = node_at(thiz, index);
    } else {
        node_destroy(new);
        return ERR;
    }
    if (target != NULL) {
        target->pre->nxt = new;
        new->pre = target->pre;
        new->nxt = target;
        target->pre = new;
        thiz->size++;
        return OK;
    }
    node_destroy(new);
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
        node_destroy(target);
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
    Node *itr = thiz->head->nxt;
    if (itr != thiz->tail) {
        visit(ctx, itr->data, true);
        itr = itr->nxt;
    }
    while (itr != thiz->tail) {
        visit(ctx, itr->data, false);
        itr = itr->nxt;
    }
    return OK;
}

#ifdef DLIST_TEST

#include <assert.h>

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

void test_int_dlist()
{
    int n = 10;
    void *data = NULL;

    DList* d = dlist_create();
    assert(dlist_size(d) == 0);

    /* append */
    for(int i = 0, j = 0; i < n; i++) {
        data = malloc(sizeof(int));
        *(int *)data = i;
        assert(dlist_append(d, (void *)data) == OK);
        assert(dlist_size(d) == (i + 1));
        assert(dlist_get_by_index(d, i, (void **)&data) == OK);
        assert(*(int *)data == i);
    }
    assert(dlist_size(d) == n);
    print(d);

    for(int i = 0; i < n; i++) {
        data = malloc(sizeof(int));
        *(int *)data = i * 2;
        assert(dlist_set_by_index(d, i, (void *)data) == OK);
        assert(dlist_get_by_index(d, i, (void **)&data) == OK);
        assert(*(int *)data == 2 * i);
    }
    assert(dlist_size(d) == n);
    print(d);

    for(int i = 0; i < n; i++) {
        assert(dlist_get_by_index(d, 0, (void **)&data) == OK);
        assert(*(int *)data == i * 2);
        printf("%d\n", *(int *)data);
        assert(dlist_size(d) == (n - i));
        assert(dlist_delete(d, 0) == OK);
        free(data);
        print(d);
        assert(dlist_size(d) == (n - i - 1));
    }
    assert(dlist_size(d) == 0);


}

int main()
{
    test_int_dlist();
    return 0;
}

#endif
