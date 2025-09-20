#ifndef SVEC_H
#define SVEC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline void* xmalloc(int size) {
    void* p = malloc(size);
    if (!p) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(1);
    }
    return p;
}


static inline void* xrealloc(void* p, int size) {
    void* e = realloc(p, size);
    if (!e) {
        fprintf(stderr, "error: unable to allocate memory\n");
        exit(1);
    }
    return e;
}

typedef struct {
    void* p;
    int size; 
    int totalSize;
    int elemSize;
} Array;

static inline Array* svec_init_array(int elemSize, int totalSize) {
        Array* arr = (Array*) xmalloc(sizeof(*arr));
        arr->totalSize = totalSize;
        arr->size = 0;
        arr->elemSize = elemSize;
        arr->p = xmalloc(arr->totalSize * arr->size);
        return arr;
}

static inline void svec_free_array(Array* arr) {
    free(arr->p);
    free(arr);
}

static inline void svec_push_array(Array* arr, void* value) {
    if (arr->size >= arr->totalSize) {                
        arr->totalSize += 5;
        arr->p = xrealloc(arr->p, arr->elemSize * arr->totalSize); 
    }
    void* dst = ((char*) arr->p) + (arr->elemSize * arr->size);
    memcpy(dst, value, arr->elemSize);
    arr->size++;
}



static inline void svec_pull_array(Array* arr, void* outVal) {
    void* source = ((char*) arr->p) + (arr->elemSize * --arr->size);
    memcpy(outVal, source, arr->elemSize);
}

static inline void svec_get_array(Array* arr, int index, void* outVal) {
    if (index < 0 || index >= arr->totalSize) {
        fprintf(stderr, "array out of bounds exceptions\n");
        exit(1);
    }
    void* source = ((char*) arr->p) + (arr->elemSize * index);
    memcpy(outVal, source, arr->elemSize);
}

#endif
