#include <stdio.h>

typedef struct Node Node;
struct Node {
    int data;
    Node *pre;
    Node *nxt;
};
typedef struct Node *List;

Node *get_first(List *this);
Node *get_last(List *this);
void insert_first(List *this, Node *new);
void insert_last(List *this, Node *new);
void insert_after(List *this, Node *node, Node *new);
void insert_before(List *this, Node *node, Node *new);
void remove_first(List *this);
void remove_last(List *this);
void remove_node(List *this, Node *node);

int main () {
}
