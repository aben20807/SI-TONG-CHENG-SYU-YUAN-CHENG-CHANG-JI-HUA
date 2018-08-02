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
}

Dlist *new() {
    Dlist *ret = malloc(sizeof(Dlist));
    ret->size = 0;
    ret->head = NULL;
    ret->tail = NULL;
    return ret;
}

void insert_first(Dlist *this, Node *new);
void insert_last(Dlist *this, Node *new);
void insert_after(Dlist *this, Node *node, Node *new);
void insert_before(Dlist *this, Node *node, Node *new);
void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);
