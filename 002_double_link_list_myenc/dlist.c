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

static Node *node_at(DList *this, const int index)
{
    if (this == NULL || 0 > index || index >= this->size) {
        return NULL;
    }
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
    Node *new = node_create(data);
    if (this == NULL || data == NULL || new == NULL) {
        return ERR;
    }
    if (index == 0) {
        if (this->head == NULL) {
            this->head = new;
            this->tail = this->head;
        } else {
            this->head->pre = new;
            new->nxt = this->head;
            this->head = new;
        }
        this->size++;
        return OK;
    } else if (index == this->size) {
        if (this->tail == NULL) {
            this->tail = new;
            this->head = this->head;
        } else {
            this->tail->nxt = new;
            new->pre = this->tail;
            this->tail = new;
        }
        this->size++;
        return OK;
    } else if (0 < index && index < this->size) {
        Node *target = node_at(this, index);
        if (target != NULL) {
            target->pre->nxt = new;
            new->pre = target->pre;
            new->nxt = target;
            target->pre = new;
            this->size++;
            return OK;
        }
    } else {
        return ERR;
    }
}

Status dlist_prepend(DList *this, void *data)
{
    return dlist_insert(this, 0, data);
}

Status dlist_append(DList *this, void *data)
{
    return dlist_insert(this, this->size, data);
}

Status dlist_delete(DList *this, size_t index)
{
    if (this == NULL) {
        return ERR;
    }
    Node *target = node_at(this, index);
    if (target != NULL) {
        if (target->pre == NULL) {
            target->nxt->pre = NULL;
            this->head = target->nxt;
        } else if (target->nxt == NULL) {
            target->pre->nxt = NULL;
            this->tail = target->pre;
        } else {
            Node ret = *(target);
            target->nxt->pre = target->pre;
            target->pre->nxt = target->nxt;
        }
        free(target);
        target = NULL;
        this->size--;
        return OK;
    }
    return ERR;
}

Status dlist_get_by_index(DList *this, size_t index, void **data)
{
    if (this == NULL) {
        return ERR;
    }
    Node *target = node_at(this, index);
    if (target != NULL) {
        *data = target->data;
        return OK;
    }
    return ERR;
}

Status dlist_set_by_index(DList *this, size_t index, void *data)
{
    if (this == NULL) {
        return ERR;
    }
    Node *target = node_at(this, index);
    if (target != NULL) {
        target->data = data;
        return OK;
    }
    return ERR;
}

size_t dlist_size(const DList *this)
{
    return this->size;
}

void dlist_print(const DList *this) {
    if (this == NULL) {
        return;
    }
    printf("size: %d, list: ", this->size);
    Node *cur = this->head;
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
