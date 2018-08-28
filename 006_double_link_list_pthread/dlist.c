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
    Locker *locker;
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

static void dlist_lock(DList *thiz)
{
    if (thiz->locker != NULL) {
        locker_lock(thiz->locker);
    }
}

static void dlist_unlock(DList *thiz)
{
    if (thiz->locker != NULL) {
        locker_unlock(thiz->locker);
    }
}

static void dlist_locker_destroy(DList *thiz)
{
    if (thiz->locker != NULL) {
        locker_unlock(thiz->locker);
        locker_destroy(thiz->locker);
    }
}

DList *dlist_create(Locker *locker)
{
    DList *ret = calloc(1, sizeof(DList));
    if (ret != NULL) {
        ret->size = 0;
        ret->head = calloc(1, sizeof(Node));
        ret->tail = calloc(1, sizeof(Node));
        ret->head->nxt = ret->tail;
        ret->tail->pre = ret->head;
        ret->locker = locker;
    }
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

Ret dlist_insert(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL && data != NULL, ERR);
    Node *new = node_create(data);
    return_val_if_fail(new != NULL, ERR);
    Node *target = NULL;
    if (index == thiz->size) {
        target = thiz->tail;
    } else {
        target = node_at(thiz, index);
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

Ret dlist_prepend(DList *thiz, void *data)
{
    return dlist_insert(thiz, 0, data);
}

Ret dlist_append(DList *thiz, void *data)
{
    int index = dlist_size(thiz);
    return_val_if_fail(index != -1, ERR);
    return dlist_insert(thiz, index, data);
}

Ret dlist_delete(DList *thiz, size_t index)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *target = node_at(thiz, index);
    return_val_if_fail(target != NULL, ERR);
    target->nxt->pre = target->pre;
    target->pre->nxt = target->nxt;
    node_destroy(target);
    thiz->size--;
    return OK;
}

Ret dlist_get_by_index(DList *thiz, size_t index, void **data)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *target = node_at(thiz, index);
    return_val_if_fail(target != NULL, ERR);
    *data = target->data;
    return OK;
}

Ret dlist_set_by_index(DList *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL, ERR);
    Node *target = node_at(thiz, index);
    return_val_if_fail(target != NULL, ERR);
    target->data = data;
    return OK;
}

size_t dlist_size(const DList *thiz)
{
    return_val_if_fail(thiz != NULL, -1);
    return thiz->size;
}

Ret dlist_foreach(DList *thiz, DListVisitFunc visit, void *ctx)
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
#include <time.h>
#include "locker_pthread.h"

Ret print_int(void *ctx, void *data, bool is_first)
{
    if (is_first) {
        printf("%d", *(int *)data);
    } else {
        printf(" - %d", *(int *)data);
    }
    return OK;
}

void print(DList *thiz)
{
    printf("size: %ld, list: ", dlist_size(thiz));
    dlist_foreach(thiz, print_int, NULL);
    printf("\n");
}

void clear(DList *thiz, int n)
{
    /* dlist_delete */
    void *data = NULL;
    for(int i = 0; i < n; i++) {
        assert(dlist_get_by_index(thiz, 0, (void **)&data) == OK);
        assert(dlist_size(thiz) == (n - i));
        assert(dlist_delete(thiz, 0) == OK);
        free(data);
        assert(dlist_size(thiz) == (n - i - 1));
    }
    assert(dlist_size(thiz) == 0);
}

void test_int_dlist()
{
    int n = 100;
    void *data = NULL;

    DList* d = dlist_create(locker_pthread_create());
    assert(dlist_size(d) == 0);

    /* dlist_append */
    for(int i = 0; i < n; i++) {
        data = malloc(sizeof(int));
        *(int *)data = i;
        assert(dlist_append(d, (void *)data) == OK);
        assert(dlist_size(d) == (i + 1));
        assert(dlist_get_by_index(d, i, (void **)&data) == OK);
        assert(*(int *)data == i);
    }
    assert(dlist_size(d) == n);
    // print(d);

    /* dlist_set_by_index */
    for(int i = 0; i < n; i++) {
        data = malloc(sizeof(int));
        *(int *)data = i * 2;
        assert(dlist_set_by_index(d, i, (void *)data) == OK);
        assert(dlist_get_by_index(d, i, (void **)&data) == OK);
        assert(*(int *)data == 2 * i);
    }
    assert(dlist_size(d) == n);
    // print(d);

    /* dlist_delete */
    for(int i = 0; i < n; i++) {
        assert(dlist_get_by_index(d, 0, (void **)&data) == OK);
        assert(*(int *)data == i * 2);
        // printf("%d\n", *(int *)data);
        assert(dlist_size(d) == (n - i));
        assert(dlist_delete(d, 0) == OK);
        free(data);
        // print(d);
        assert(dlist_size(d) == (n - i - 1));
    }
    assert(dlist_size(d) == 0);

    /* dlist_prepend */
    for(int i = 0; i < n; i++) {
        data = malloc(sizeof(int));
        *(int *)data = i;
        assert(dlist_prepend(d, (void *)data) == OK);
        assert(dlist_size(d) == (i + 1));
        assert(dlist_get_by_index(d, 0, (void **)&data) == OK);
        assert(*(int *)data == i);
        // print(d);
    }
    assert(dlist_size(d) == n);

    clear(d, n);
    assert(dlist_size(d) == 0);

    /* dlist_insert */
    srand(time(NULL));
    for(int i = 1; i <= n; i++) {
        data = malloc(sizeof(int));
        int random = (rand() % i);
        // printf("%d\n", random);
        *(int *)data = i;
        assert(dlist_insert(d, random, (void *)data) == OK);
        assert(dlist_size(d) == (i));
        assert(dlist_get_by_index(d, random, (void **)&data) == OK);
        assert(*(int *)data == i);
        // print(d);
    }
    assert(dlist_size(d) == n);

    clear(d, n);
    assert(dlist_size(d) == 0);
    dlist_destroy(d);
}

void test_err()
{
    printf("===========Warning is normal begin==============\n");
	assert(dlist_size(NULL) == -1);
	assert(dlist_prepend(NULL, 0) == ERR);
	assert(dlist_append(NULL, 0) == ERR);
	assert(dlist_delete(NULL, 0) == ERR);
	assert(dlist_insert(NULL, 0, 0) == ERR);
	assert(dlist_set_by_index(NULL, 0, NULL) == ERR);
	assert(dlist_get_by_index(NULL, 0, NULL) == ERR);
	assert(dlist_foreach(NULL, NULL, NULL) == ERR);
	printf("===========Warning is normal end==============\n");
}

int main()
{
    test_int_dlist();
    test_err();
    return 0;
}

#endif
