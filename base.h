#ifndef BASE_H
#define BASE_H

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
} string_view;

static inline string_view sv(const char* str) {
    return (string_view){
        .ptr = str,
        .len = strlen(str),
    };
}

static inline string_view sv_substr(string_view sv, size_t start, size_t len) {
    sv.ptr += start;
    sv.len = len;
    return sv;
}

static inline string_view sv_slice(string_view sv, size_t start, size_t end) {
    sv.ptr += start;
    sv.len = end - start;
    return sv;
}

#endif
