#ifndef _DLIST_H
#define _DLIST_H

#include <stddef.h>

typedef struct _DList DList;

DList *dlist_create(void);
void dlist_insert(DList *this, size_t index, void *data);
void dlist_prepend(DList *this, void *data);
void dlist_append(DList *this, void *data);
void dlist_delete(DList *this, size_t index);
void dlist_get_by_index(DList *this, size_t index, void **data);
void dlist_set_by_index(DList *this, size_t index, void *data);
size_t dlist_length(DList *this);

#endif
