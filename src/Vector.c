#include "Vector.h"

#include <stdlib.h>



#define CSSOM_VECTOR_DEFINE(T, suffix) \
  struct _CSSOM_Vector_##suffix { \
    T *data; \
    size_t size; \
    size_t capacity; \
    CSSOM_VectorIter_##suffix end; \
  }; \
  \
  \
  \
  static CSSOM_Vector_##suffix* Vector_##suffix##_enlarge( \
    CSSOM_Vector_##suffix *vector) \
  { \
    size_t capacity; \
    T *data; \
    \
    if (vector->capacity != 0) { \
      capacity = vector->capacity + vector->capacity / 2; \
    } else { \
      capacity = 4; \
    } \
    \
    data = (T*)realloc(vector->data, sizeof(T) * capacity); \
    if (data == NULL) return NULL; \
    \
    vector->capacity = capacity; \
    vector->data = data; \
    vector->end = &data[vector->size]; \
    return vector; \
  } \
  \
  \
  \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc(size_t size) { \
    T *data; \
    CSSOM_Vector_##suffix *vector; \
    \
    data = (T*)malloc(sizeof(T) * size); \
    if (size != 0 && data == NULL) return NULL; \
    \
    vector = (CSSOM_Vector_##suffix*)malloc( \
      sizeof(CSSOM_Vector_##suffix)); \
    if (vector == NULL) { \
      free(data); \
      return NULL; \
    } \
    \
    vector->data = data; \
    vector->size = size; \
    vector->capacity = size; \
    vector->end = &data[size]; \
    \
    return vector; \
  } \
  \
  \
  \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc_ex( \
    size_t size, size_t capacity) \
  { \
    T *data; \
    CSSOM_Vector_##suffix *vector; \
    \
    data = (T*)malloc(sizeof(T) * capacity); \
    if (capacity != 0 && data == NULL) return NULL; \
    \
    vector = (CSSOM_Vector_##suffix*)malloc( \
      sizeof(CSSOM_Vector_##suffix)); \
    if (vector == NULL) { \
      free(data); \
      return NULL; \
    } \
    \
    vector->data = data; \
    vector->size = size; \
    vector->capacity = capacity; \
    vector->end = &data[capacity]; \
    \
    return vector; \
  } \
  \
  \
  \
  void CSSOM_Vector_##suffix##_free(CSSOM_Vector_##suffix *vector) { \
    free(vector->data); \
    free(vector); \
  }\
  \
  \
  \
  size_t CSSOM_Vector_##suffix##_size(const CSSOM_Vector_##suffix *vector) { \
    return vector->size; \
  } \
  \
  \
  \
  size_t CSSOM_Vector_##suffix##_capacity( \
    const CSSOM_Vector_##suffix *vector) \
  { \
    return vector->capacity; \
  } \
  \
  \
  \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_append( \
    CSSOM_Vector_##suffix *vector, T value) \
  { \
    if (vector->size == vector->capacity) { \
      if (Vector_##suffix##_enlarge(vector) == NULL) { \
        return CSSOM_Vector_##suffix##_end(vector); \
      } \
    } \
    \
    vector->data[vector->size] = value; \
    ++vector->size; \
    vector->end = &vector->data[vector->size]; \
    return &vector->data[vector->size - 1]; \
  } \
  \
  \
  \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_begin( \
    CSSOM_Vector_##suffix *vector) \
  { \
    return vector->data; \
  } \
  \
  \
  \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_end( \
    CSSOM_Vector_##suffix *vector) \
  { \
    return vector->end; \
  } \
  \
  \
  \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cbegin( \
    const CSSOM_Vector_##suffix *vector) \
  { \
    return vector->data; \
  } \
  \
  \
  \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cend( \
    const CSSOM_Vector_##suffix *vector) \
  { \
    return vector->end; \
  } \
  \
  \
  \
  CSSOM_VectorIter_##suffix CSSOM_VectorIter_##suffix##_next( \
    CSSOM_VectorIter_##suffix iter) \
  { \
    return ++iter; \
  } \
  \
  \
  \
  CSSOM_VectorConstIter_##suffix CSSOM_VectorConstIter_##suffix##_next( \
    CSSOM_VectorConstIter_##suffix iter) \
  { \
    return ++iter; \
  }
