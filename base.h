#include <string.h>

#define MIN(a, b) ({      \
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _a < _b ? _a : _b;    \
})

#define MAX(a, b) ({      \
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _a > _b ? _a : _b;    \
})

#define SUB_SAT(a, b) ({    \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a - _b : 0;  \
})

#define SV_FMT     "%.*s"
#define SV_ARG(sv) (int)(sv).len, (sv).ptr

typedef struct {
    const char*  ptr;
    size_t       len;
} string_view_t;

static inline string_view_t string_view(const char* str) {
    return (string_view_t){
        .ptr = str,
        .len = strlen(str),
    };
}
