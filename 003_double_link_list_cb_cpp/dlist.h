#ifndef _DLIST_H
#define _DLIST_H

#include <stddef.h>

typedef struct _DList DList;
typedef enum {OK, ERR} Status;

DList *dlist_create(void);
Status dlist_insert(DList *this, size_t index, void *data);
Status dlist_prepend(DList *this, void *data);
Status dlist_append(DList *this, void *data);
Status dlist_delete(DList *this, size_t index);
Status dlist_get_by_index(DList *this, size_t index, void **data);
Status dlist_set_by_index(DList *this, size_t index, void *data);
size_t dlist_size(const DList *this);
void dlist_print(const DList *this);

#endif
