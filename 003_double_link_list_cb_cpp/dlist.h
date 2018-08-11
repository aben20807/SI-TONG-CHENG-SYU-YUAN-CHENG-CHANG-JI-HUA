#ifndef _DLIST_H
#define _DLIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DList DList;
typedef enum {OK, ERR} DListRet;

DList *dlist_create(void);
DListRet dlist_insert(DList *thiz, size_t index, void *data);
DListRet dlist_prepend(DList *thiz, void *data);
DListRet dlist_append(DList *thiz, void *data);
DListRet dlist_delete(DList *thiz, size_t index);
DListRet dlist_get_by_index(DList *thiz, size_t index, void **data);
DListRet dlist_set_by_index(DList *thiz, size_t index, void *data);
size_t dlist_size(const DList *thiz);
void dlist_print(const DList *thiz);

#ifdef __cplusplus
}
#endif

#endif
