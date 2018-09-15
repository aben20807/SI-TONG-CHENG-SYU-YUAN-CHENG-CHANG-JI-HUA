#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum _Ret {
    RET_OK,
    RET_FAIL,
    RET_INVALID_PARAMS,
} Ret;

#define return_if_fail(p) \
    if (!(p)) { \
        printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__); \
        return; \
    }

#define return_val_if_fail(p, ret) \
    if (!(p)) { \
        printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__); \
        return (ret); \
    }

#endif /* TYPEDEF_H */
