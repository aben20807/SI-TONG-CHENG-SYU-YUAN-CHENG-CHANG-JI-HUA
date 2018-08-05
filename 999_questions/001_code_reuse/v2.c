Status dlist_insert(DList *this, size_t index, void *data)
{
    if (this == NULL || data == NULL) {
        return ERR;
    }
    if (index == 0) {
        return dlist_prepend(this, data);
    } else if (index == this->size) {
        return dlist_append(this, data);
    } else if (0 < index && index < this->size) {
        Node *new = node_create(data);
        Node *target = node_at(this, index);
        if (target != NULL && new != NULL) {
            target->pre->nxt = new;
            new->pre = target->pre;
            new->nxt = target;
            target->pre = new;
            this->size++;
            return OK;
        }
    }
    return ERR;
}

Status dlist_prepend(DList *this, void *data)
{
    Node *new = node_create(data);
    if (this == NULL || data == NULL || new == NULL) {
        return ERR;
    }
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
}

Status dlist_append(DList *this, void *data)
{
    Node *new = node_create(data);
    if (this == NULL || data == NULL || new == NULL) {
        return ERR;
    }
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
}
