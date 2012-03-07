#include "Deque.h"

#include "Vector.h"
#include "Vector.c"

#include <stdlib.h>



#define CSSOM_DEQUE_DEFINE(T, suffix) \
  struct _CSSOM_DequeItem_##suffix { \
    T value; \
    size_t index; \
    struct _CSSOM_DequeItem_##suffix *prev; \
    struct _CSSOM_DequeItem_##suffix *next; \
  }; \
  \
  \
  \
  CSSOM_VECTOR_DECLARE(struct _CSSOM_DequeItem_##suffix*, DequeItem_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(struct _CSSOM_DequeItem_##suffix*, DequeItem_##suffix) \
  \
  \
  \
  static struct _CSSOM_DequeItem_##suffix* \
  DequeItem_##suffix##_alloc(size_t index) \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    \
    item = (struct _CSSOM_DequeItem_##suffix*)malloc( \
      sizeof(struct _CSSOM_DequeItem_##suffix)); \
    if (item == NULL) return NULL; \
    \
    item->index = index; \
    item->prev = NULL; \
    item->next = NULL; \
    \
    return item; \
  } \
  \
  \
  \
  static void DequeItem_##suffix##_free( \
    struct _CSSOM_DequeItem_##suffix *item) \
  { \
    free(item); \
  } \
  \
  \
  \
  static void DequeItem_##suffix##_freeAll( \
    struct _CSSOM_DequeItem_##suffix *item) \
  { \
    struct _CSSOM_DequeItem_##suffix *next; \
    \
    for (; item != NULL; item = next) { \
      next = item->next; \
      DequeItem_##suffix##_free(item); \
    } \
  } \
  \
  \
  \
  struct _CSSOM_Deque_##suffix { \
    struct _CSSOM_DequeItem_##suffix *head; \
    struct _CSSOM_DequeItem_##suffix *tail; \
    CSSOM_Vector_DequeItem_##suffix *refs; \
  }; \
  \
  \
  \
  CSSOM_Deque_##suffix* CSSOM_Deque_##suffix##_alloc(size_t size) { \
    CSSOM_Vector_DequeItem_##suffix *refs; \
    struct _CSSOM_DequeItem_##suffix **referencesraw; \
    struct _CSSOM_DequeItem_##suffix *item; \
    struct _CSSOM_DequeItem_##suffix *at; \
    CSSOM_Deque_##suffix *deque; \
    size_t i; \
    \
    refs = CSSOM_Vector_DequeItem_##suffix##_alloc(size); \
    if (refs == NULL) return NULL; \
    \
    referencesraw = &*CSSOM_Vector_DequeItem_##suffix##_begin(refs); \
    \
    item = DequeItem_##suffix##_alloc((size_t)-1); \
    if (item == NULL) { \
      CSSOM_Vector_DequeItem_##suffix##_free(refs); \
      return NULL; \
    } \
    \
    for (i = 0, at = item; i < size; ++i, at = at->next) { \
      at->next = DequeItem_##suffix##_alloc(i); \
      if (at->next == NULL) { \
        CSSOM_Vector_DequeItem_##suffix##_free(refs); \
        DequeItem_##suffix##_freeAll(item); \
        return NULL; \
      } \
      \
      referencesraw[i] = at->next; \
      \
      at->next->prev = at; \
    } \
    \
    deque = (CSSOM_Deque_##suffix*)malloc(sizeof(CSSOM_Deque_##suffix)); \
    if (deque == NULL) { \
      CSSOM_Vector_DequeItem_##suffix##_free(refs); \
      DequeItem_##suffix##_freeAll(item); \
      return NULL; \
    } \
    \
    deque->refs = refs; \
    deque->head = item; \
    deque->tail = at; \
    \
    return deque; \
  } \
  \
  \
  \
  void CSSOM_Deque_##suffix##_free(CSSOM_Deque_##suffix *deque) { \
    CSSOM_Vector_DequeItem_##suffix##_free(deque->refs); \
    DequeItem_##suffix##_freeAll(deque->head); \
    free(deque); \
  } \
  \
  \
  \
  size_t CSSOM_Deque_##suffix##_size(const CSSOM_Deque_##suffix *deque) { \
    return CSSOM_Vector_DequeItem_##suffix##_size(deque->refs); \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_append( \
    CSSOM_Deque_##suffix *deque, T value) \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    CSSOM_VectorIter_DequeItem_##suffix it; \
    \
    item = DequeItem_##suffix##_alloc(CSSOM_Deque_##suffix##_size(deque)); \
    if (item == NULL) return CSSOM_Deque_##suffix##_end(deque); \
    \
    it = CSSOM_Vector_DequeItem_##suffix##_append(deque->refs, item); \
    if (it == CSSOM_Vector_DequeItem_##suffix##_end(deque->refs)) { \
      DequeItem_##suffix##_free(item); \
      return CSSOM_Deque_##suffix##_end(deque); \
    } \
    \
    item->value = value; \
    item->prev = deque->tail; \
    deque->tail->next = item; \
    deque->tail = item; \
    \
    return (CSSOM_DequeIter_##suffix)item; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_insert( \
    CSSOM_Deque_##suffix *deque, CSSOM_DequeIter_##suffix position, T value) \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    struct _CSSOM_DequeItem_##suffix *at; \
    CSSOM_VectorIter_DequeItem_##suffix refit; \
    \
    if (position == CSSOM_Deque_##suffix##_end(deque)) \
      return CSSOM_Deque_##suffix##_append(deque, value); \
    \
    at = (struct _CSSOM_DequeItem_##suffix*)position; \
    refit = (CSSOM_VectorIter_DequeItem_##suffix) \
      (CSSOM_Vector_DequeItem_##suffix##_begin(deque->refs) + at->index); \
    item = DequeItem_##suffix##_alloc(at->index); \
    if (item == NULL) return CSSOM_Deque_##suffix##_end(deque); \
    \
    refit = CSSOM_Vector_DequeItem_##suffix##_insert(deque->refs, \
      refit, item); \
    if (refit == CSSOM_Vector_DequeItem_##suffix##_end(deque->refs)) { \
      DequeItem_##suffix##_free(item); \
      return CSSOM_Deque_##suffix##_end(deque); \
    } \
    \
    item->value = value; \
    at->prev->next = item; \
    item->prev = at->prev; \
    at->prev = item; \
    item->next = at; \
    \
    for (; \
      refit != CSSOM_Vector_DequeItem_##suffix##_end(deque->refs); \
      refit = CSSOM_VectorIter_DequeItem_##suffix##_next(refit)) \
    { \
      ++(**refit).index; \
    } \
    \
    return (CSSOM_DequeIter_##suffix)item; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_erase( \
    CSSOM_Deque_##suffix *deque, CSSOM_DequeIter_##suffix position) \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    struct _CSSOM_DequeItem_##suffix *at; \
    CSSOM_VectorIter_DequeItem_##suffix refit; \
    \
    at = (struct _CSSOM_DequeItem_##suffix*)position; \
    refit = (CSSOM_VectorIter_DequeItem_##suffix) \
      (CSSOM_Vector_DequeItem_##suffix##_begin(deque->refs) + at->index); \
    item = at->next; \
    \
    refit = CSSOM_Vector_DequeItem_##suffix##_erase(deque->refs, refit); \
    \
    at->prev->next = item; \
    if (item != NULL) item->prev = at->prev; \
    DequeItem_##suffix##_free(at); \
    \
    for (; \
      refit != CSSOM_Vector_DequeItem_##suffix##_end(deque->refs); \
      refit = CSSOM_VectorIter_DequeItem_##suffix##_next(refit)) \
    { \
      --(**refit).index; \
    } \
    \
    return (CSSOM_DequeIter_##suffix)item; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_begin( \
    CSSOM_Deque_##suffix *deque) \
  { \
    return (CSSOM_DequeIter_##suffix)deque->head->next; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_end( \
    CSSOM_Deque_##suffix *deque) \
  { \
    return (CSSOM_DequeIter_##suffix)deque->tail->next; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_at( \
    CSSOM_Deque_##suffix *deque, size_t index) \
  { \
    return (CSSOM_DequeIter_##suffix) \
      *(CSSOM_Vector_DequeItem_##suffix##_begin(deque->refs) + index); \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_DequeIter_##suffix##_next( \
    CSSOM_DequeIter_##suffix iter) \
  { \
    return (CSSOM_DequeIter_##suffix) \
      ((struct _CSSOM_DequeItem_##suffix*)iter)->next; \
  }
