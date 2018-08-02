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
Node *search(Dlist *this, int target);
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
    insert_after(d, search(d, 1), new_node(6));
    insert_after(d, search(d, 5), new_node(7));
    print_list(d);
    insert_before(d, search(d, 1), new_node(8));
    insert_before(d, search(d, 3), new_node(9));
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

Node *search(Dlist *this, int target) {
    if (this == NULL) {
        return NULL;
    }
    Node *cur = this->head;
    while (cur != NULL) {
        if (cur->data == target) {
            return cur;
        }
        cur = cur->nxt;
    }
    return NULL;
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
    if (this == NULL && new == NULL) {
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
    if (this == NULL && new == NULL) {
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
    if (this == NULL && node == NULL && new == NULL) {
        return;
    }
    this->size++;
    if (node->nxt == NULL) {
        node->nxt = new;
        new->pre = node;
        this->tail = new;
    } else {
        new->nxt = node->nxt;
        new->pre = node;
        new->nxt->pre = new;
        new->pre->nxt = new;
    }
}

void insert_before(Dlist *this, Node *node, Node *new) {
    if (this == NULL && node == NULL && new == NULL) {
        return;
    }
    this->size++;
    if (node->pre == NULL) {
        node->pre = new;
        new->nxt = node;
        this->head = new;
    } else {
        new->pre = node->pre;
        new->nxt = node;
        new->pre->nxt = new;
        new->nxt->pre = new;
    }
}

void remove_first(Dlist *this);
void remove_last(Dlist *this);
void remove_node(Dlist *this, Node *node);
