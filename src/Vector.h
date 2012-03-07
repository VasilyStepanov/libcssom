#ifndef CSSOM_VECTOR_H
#define CSSOM_VECTOR_H

#include <stddef.h>



#define CSSOM_VECTOR_DECLARE(T, suffix) \
  typedef struct _CSSOM_Vector_##suffix CSSOM_Vector_##suffix; \
  typedef T* CSSOM_VectorIter_##suffix; \
  typedef T const * CSSOM_VectorConstIter_##suffix; \
  \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc(size_t size); \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc_ex(size_t size, \
    size_t capacity); \
  void CSSOM_Vector_##suffix##_free(CSSOM_Vector_##suffix *vector); \
  size_t CSSOM_Vector_##suffix##_size(const CSSOM_Vector_##suffix *vector); \
  size_t CSSOM_Vector_##suffix##_capacity( \
    const CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_append( \
    CSSOM_Vector_##suffix *vector, T value); \
  void CSSOM_Vector_##suffix##_pop(CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_insert( \
    CSSOM_Vector_##suffix *vector, \
    CSSOM_VectorIter_##suffix position, T value); \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_erase( \
    CSSOM_Vector_##suffix *vector, CSSOM_VectorIter_##suffix position); \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cbegin( \
    const CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cend( \
    const CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_begin( \
    CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorIter_##suffix CSSOM_Vector_##suffix##_end( \
    CSSOM_Vector_##suffix *vector); \
  \
  CSSOM_VectorIter_##suffix CSSOM_VectorIter_##suffix##_next( \
    CSSOM_VectorIter_##suffix iter); \
  CSSOM_VectorConstIter_##suffix CSSOM_VectorConstIter_##suffix##_next( \
    CSSOM_VectorConstIter_##suffix iter);



#endif
