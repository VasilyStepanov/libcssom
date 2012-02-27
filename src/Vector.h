#ifndef CSSOM_VECTOR_H
#define CSSOM_VECTOR_H

#include <stddef.h>



#define CSSOM_VECTOR_DECLARE(T, suffix) \
  typedef struct _CSSOM_Vector_##suffix CSSOM_Vector_##suffix; \
  typedef T* CSSOM_VectorIter_##suffix; \
  typedef const T* CSSOM_VectorConstIter_##suffix; \
  \
  CSSOM_Vector_##suffix* CSSOM_Vector_##suffix##_alloc(size_t size); \
  void CSSOM_Vector_##suffix##_free(CSSOM_Vector_##suffix *vector); \
  size_t CSSOM_Vector_##suffix##_size(CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cbegin( \
    CSSOM_Vector_##suffix *vector); \
  CSSOM_VectorConstIter_##suffix CSSOM_Vector_##suffix##_cend( \
    CSSOM_Vector_##suffix *vector); \
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
