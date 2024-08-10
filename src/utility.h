#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
    void **data;
    u64 used, capacity;
} ArrayList;

static void initArray(ArrayList *a, u64 initial_size) {
    a->data = calloc(initial_size, sizeof(void *));
    a->used = 0;
    a->capacity = initial_size;
}

static void insertArray(ArrayList *a, void *element) {
    if (a->used == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, a->capacity * sizeof(void *));
    }

    a->data[a->used++] = element;
}

static void deleteArray(ArrayList *a, u64 i) {
    if (i >= a->capacity) {
        return;
    }

    a->data[i] = NULL;

    for (u64 index = i; index < a->capacity - 1; index++) {
        a->data[index] = a->data[index + 1];
        a->data[index + 1] = NULL;
    }

    --a->capacity;
}

static void freeArray(ArrayList *a) {
    free(a->data);
    a->data = NULL;
    a->used = 0;
    a->capacity = 0;
}

#endif