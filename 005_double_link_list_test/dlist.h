#ifndef _DLIST_H
#define _DLIST_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DList DList;
typedef enum {OK, ERR} DListRet;
typedef DListRet (*DListVisitFunc)(void *ctx, void *data, bool is_first);

DList *dlist_create(void);
void dlist_destroy(DList* thiz);
DListRet dlist_insert(DList *thiz, size_t index, void *data);
DListRet dlist_prepend(DList *thiz, void *data);
DListRet dlist_append(DList *thiz, void *data);
DListRet dlist_delete(DList *thiz, size_t index);
DListRet dlist_get_by_index(DList *thiz, size_t index, void **data);
DListRet dlist_set_by_index(DList *thiz, size_t index, void *data);
size_t dlist_size(const DList *thiz);
DListRet dlist_foreach(DList *thiz, DListVisitFunc visit, void *ctx);

#define return_if_fail(p) \
    if(!(p)) { \
        printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__); \
        return; \
    }
#define return_val_if_fail(p, ret) \
    if(!(p)) { \
        printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__); \
        return (ret); \
    }

#ifdef __cplusplus
}
#endif

#endif
