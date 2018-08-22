#ifndef _DLIST_H
#define _DLIST_H

#include "locker.h"
#include "typedefs.h"

DECLS_BEGIN

typedef struct _DList DList;
typedef Ret (*DListVisitFunc)(void *ctx, void *data, bool is_first);

DList *dlist_create(Locker *locker);
void dlist_destroy(DList* thiz);
Ret dlist_insert(DList *thiz, size_t index, void *data);
Ret dlist_prepend(DList *thiz, void *data);
Ret dlist_append(DList *thiz, void *data);
Ret dlist_delete(DList *thiz, size_t index);
Ret dlist_get_by_index(DList *thiz, size_t index, void **data);
Ret dlist_set_by_index(DList *thiz, size_t index, void *data);
size_t dlist_size(const DList *thiz);
Ret dlist_foreach(DList *thiz, DListVisitFunc visit, void *ctx);

DECLS_END

#endif /* _DLIST_H */
