#ifndef CSSOM_DEQUE_H
#define CSSOM_DEQUE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_DEQUE_DECLARE(T, suffix) \
  typedef struct _CSSOM_Deque_##suffix CSSOM_Deque_##suffix; \
  typedef T* CSSOM_DequeIter_##suffix; \
  typedef T const * CSSOM_DequeConstIter_##suffix; \
  \
  CSSOM_Deque_##suffix* CSSOM_Deque_##suffix##_alloc(size_t size); \
  CSSOM_Deque_##suffix* CSSOM_Deque_##suffix##_alloc_ex(size_t size, \
    size_t capacity); \
  void CSSOM_Deque_##suffix##_free(CSSOM_Deque_##suffix *deque); \
  size_t CSSOM_Deque_##suffix##_size(const CSSOM_Deque_##suffix *deque); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_append( \
    CSSOM_Deque_##suffix *deque, T value); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_insert( \
    CSSOM_Deque_##suffix *deque, CSSOM_DequeIter_##suffix position, T value); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_erase( \
    CSSOM_Deque_##suffix *deque, CSSOM_DequeIter_##suffix position); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_begin( \
    CSSOM_Deque_##suffix *deque); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_end( \
    CSSOM_Deque_##suffix *deque); \
  CSSOM_DequeConstIter_##suffix CSSOM_Deque_##suffix##_cbegin( \
    const CSSOM_Deque_##suffix *deque); \
  CSSOM_DequeConstIter_##suffix CSSOM_Deque_##suffix##_cend( \
    const CSSOM_Deque_##suffix *deque); \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_at( \
    CSSOM_Deque_##suffix *deque, size_t index); \
  \
  CSSOM_DequeIter_##suffix CSSOM_DequeIter_##suffix##_next( \
    CSSOM_DequeIter_##suffix iter); \
  CSSOM_DequeConstIter_##suffix CSSOM_DequeConstIter_##suffix##_next( \
    CSSOM_DequeConstIter_##suffix iter);



#ifdef __cplusplus
}
#endif

#endif
