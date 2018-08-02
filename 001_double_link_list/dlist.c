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
void print_list(Dlist *this);
void insert_first(Dlist *this, Node *new);
void insert_last(Dlist *this, Node *new);
void insert_after(Dlist *this, Node *node, Node *new);
void insert_before(Dlist *this, Node *node, Node *new);
void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);

int main () {
    Dlist *d = new();
    print_list(d);
    insert_first(d, new_node(1));
    print_list(d);
    insert_first(d, new_node(2));
    insert_first(d, new_node(3));
    print_list(d);
    insert_last(d, new_node(4));
    insert_last(d, new_node(5));
    print_list(d);
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

void print_list(Dlist *this) {
    if (this == NULL) {
        return;
    }
    printf("size: %d, list: ", this->size);
    Node *cur = this->head;
    if (cur != NULL) {
        printf("%d", cur->data);
        cur = cur->nxt;
    }
    while (cur != NULL) {
        printf(" - %d", cur->data);
        cur = cur->nxt;
    }
    printf("\n");
}

void insert_first(Dlist *this, Node *new) {
    if (this == NULL) {
        return;
    }
    this->size++;
    if (this->head == NULL) {
        this->head = new;
        this->tail = this->head;
    } else {
        this->head->pre = new;
        new->nxt = this->head;
        this->head = new;
    }
}

void insert_last(Dlist *this, Node *new) {
    if (this == NULL) {
        return;
    }
    this->size++;
    if (this->tail == NULL) {
        this->tail = new;
        this->head = this->tail;
    } else {
        this->tail->nxt = new;
        new->pre = this->tail;
        this->tail = new;
    }
}

void insert_after(Dlist *this, Node *node, Node *new) {
    // if ()
}
void insert_before(Dlist *this, Node *node, Node *new);
void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);
