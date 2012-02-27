#include "Vector.h"

#include <stdlib.h>



#define CSSOM_VECTOR_DEFINE(T, suffix) \
  struct _CSSOM_Vector_##suffix { \
    T *data; \
    size_t size; \
    CSSOM_VectorIter_##suffix end; \
  }; \
  \
  \
  \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc(size_t size) { \
    T *data; \
    CSSOM_Vector_##suffix *vector; \
    \
    data = (T*)malloc(sizeof(T) * (size + 1)); \
    if (data == NULL) return NULL; \
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
    vector->end = &data[size]; \
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
  size_t CSSOM_Vector_##suffix##_size(CSSOM_Vector_##suffix *vector) { \
    return vector->size; \
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
    CSSOM_Vector_##suffix *vector) \
  { \
    return vector->data; \
  } \
  \
  \
  \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cend( \
    CSSOM_Vector_##suffix *vector) \
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
