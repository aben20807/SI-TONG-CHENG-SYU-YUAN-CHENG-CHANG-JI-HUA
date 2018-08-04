#include "dlist.h"

typedef struct _Node {
    int data;
    struct _Node *pre;
    struct _Node *nxt;
} Node;

struct _DList {
    void *data;
    Node *head;
    Node *tail;
};
