#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum _Ret {
    RET_OK,
    RET_OOM,            // Out of memory
    RET_OOB,            // Index out of bounds
    RET_STOP,
    RET_FAIL,
    RET_INVALID_PARAMS, // Invalid parameters
} Ret;

static inline char *get_ret(Ret v)
{
    static const char *strings[] = {
        "RET_OK",
        "RET_OOM",
        "RET_OOB",
        "RET_STOP",
        "RET_FAIL",
        "RET_INVALID_PARAMS",
    };
    return (char *)strings[v];
}

#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif /* __cplusplus */

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

#endif /* _TYPEDEFS_H */
