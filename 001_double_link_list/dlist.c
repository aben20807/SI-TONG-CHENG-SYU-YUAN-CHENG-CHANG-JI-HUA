#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
    int data;
    Node *pre;
    Node *nxt;
};
typedef struct Dlist Dlist;
struct Dlist {
    int size;
    Node *head;
    Node *tail;
};

Dlist *new();
Node *new_node(int data);
void insert_first(Dlist *this, Node *new);
void insert_last(Dlist *this, Node *new);
void insert_after(Dlist *this, Node *node, Node *new);
void insert_before(Dlist *this, Node *node, Node *new);
void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);

int main () {
    Dlist *d = new();
    printf("%d\n", d->size);
    insert_first(d, new_node(1));
    printf("%d\n", d->size);
}

Dlist *new() {
    Dlist *ret = malloc(sizeof(Dlist));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

Node *new_node(int data) {
    Node *ret = malloc(sizeof(Node));
    ret->data = data;
    ret->pre = NULL;
    ret->nxt = NULL;
    return ret;
}

void insert_first(Dlist *this, Node *new) {
    this->size++;
    if (this->head == NULL) {
        this->head = new;
    } else {
        this->head->pre = new;
        new->nxt = this->head;
        this->head = new;
    }
}
void insert_last(Dlist *this, Node *new);
void insert_after(Dlist *this, Node *node, Node *new);
void insert_before(Dlist *this, Node *node, Node *new);
void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);
