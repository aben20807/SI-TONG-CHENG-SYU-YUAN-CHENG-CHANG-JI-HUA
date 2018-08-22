#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum _Ret {
    OK,
    ERR,
} Ret;

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
