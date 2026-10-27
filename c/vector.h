#ifdef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VECTOR(type, name, capacity) vector name; vector_init(&name, capacity, sizeof(type))
typedef struct{
        int capacity;
        void* items;
        size_t size0fType;
        int size;
}vector;

void vector_init(vector* v, int capacity, size_t size0fType){
        if (capacity<1) capacity = 1;
        v->capacity = capacity;
        v->items = calloc(capacity, size0fType);
        v->size = 0;
        v->size0fType = size0fType;
}

int vector_resize(vector* v, int capacity){
        void* new_items = realloc(v->items, capacity * v->size0fType);
        if (new_items == NULL) return 0;
        v->items = new_items;
        v->capacity = capacity;
        return 1;
}

int vector_push_back(vector* v, void* item){
        if (v->size >= v->capacity){
                if (!vector_resize(v, 2 * v->capacity)) {printf("realloc failed"); return 0;}
        }
        memcpy(v->items + v->size * v->size0fType, item, v->size0fType);
        v->size++;
        return 1;
}
void vector_free(vector* v){
        free(v->items); v->items = NULL; v->size = v->capacity = 0;
}
#endif