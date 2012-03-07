#include "Deque.h"

#include <stdlib.h>



#define CSSOM_DEQUE_DEFINE(T, suffix) \
  struct _CSSOM_DequeItem_##suffix { \
    T value; \
    struct _CSSOM_DequeItem_##suffix *prev; \
    struct _CSSOM_DequeItem_##suffix *next; \
  }; \
  \
  \
  \
  static struct _CSSOM_DequeItem_##suffix* \
  CSSOM_DequeItem_##suffix##_alloc() \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    \
    item = (struct _CSSOM_DequeItem_##suffix*)malloc( \
      sizeof(struct _CSSOM_DequeItem_##suffix)); \
    if (item == NULL) return NULL; \
    \
    item->prev = NULL; \
    item->next = NULL; \
    \
    return item; \
  } \
  \
  \
  \
  static void CSSOM_DequeItem_##suffix##_free( \
    struct _CSSOM_DequeItem_##suffix *item) \
  { \
    free(item); \
  } \
  \
  \
  \
  static void CSSOM_DequeItem_##suffix##_freeAll( \
    struct _CSSOM_DequeItem_##suffix *item) \
  { \
    struct _CSSOM_DequeItem_##suffix *next; \
    \
    for (; item != NULL; item = next) { \
      next = item->next; \
      CSSOM_DequeItem_##suffix##_free(item); \
    } \
  } \
  \
  \
  \
  struct _CSSOM_Deque_##suffix { \
    struct _CSSOM_DequeItem_##suffix *head; \
    struct _CSSOM_DequeItem_##suffix *tail; \
    size_t size; \
  }; \
  \
  \
  \
  CSSOM_Deque_##suffix* CSSOM_Deque_##suffix##_alloc(size_t size) { \
    struct _CSSOM_DequeItem_##suffix *item; \
    struct _CSSOM_DequeItem_##suffix *at; \
    CSSOM_Deque_##suffix *deque; \
    size_t i; \
    \
    item = CSSOM_DequeItem_##suffix##_alloc(); \
    if (item == NULL) return NULL; \
    for (i = 0, at = item; i < size; ++i, at = at->next) { \
      at->next = CSSOM_DequeItem_##suffix##_alloc(); \
      if (at->next == NULL) { \
        CSSOM_DequeItem_##suffix##_freeAll(item); \
        return NULL; \
      } \
      \
      at->next->prev = at; \
    } \
    \
    deque = (CSSOM_Deque_##suffix*)malloc(sizeof(CSSOM_Deque_##suffix)); \
    if (deque == NULL) { \
      CSSOM_DequeItem_##suffix##_free(item); \
      return NULL; \
    } \
    \
    deque->head = item; \
    deque->tail = at; \
    deque->size = size; \
    \
    return deque; \
  } \
  \
  \
  \
  void CSSOM_Deque_##suffix##_free(CSSOM_Deque_##suffix *deque) { \
    CSSOM_DequeItem_##suffix##_freeAll(deque->head); \
    free(deque); \
  } \
  \
  \
  \
  size_t CSSOM_Deque_##suffix##_size(const CSSOM_Deque_##suffix *deque) { \
    return deque->size; \
  } \
  \
  \
  \
  CSSOM_DequeIter_##suffix CSSOM_Deque_##suffix##_append( \
    CSSOM_Deque_##suffix *deque, T value) \
  { \
    struct _CSSOM_DequeItem_##suffix *item; \
    \
    item = CSSOM_DequeItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_Deque_##suffix##_end(deque); \
    \
    item->value = value; \
    item->prev = deque->tail; \
    deque->tail->next = item; \
    deque->tail = item; \
    ++deque->size; \
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
    \
    if (position == CSSOM_Deque_##suffix##_end(deque)) \
      return CSSOM_Deque_##suffix##_append(deque, value); \
    \
    at = (struct _CSSOM_DequeItem_##suffix*)position; \
    item = CSSOM_DequeItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_Deque_##suffix##_end(deque); \
    \
    item->value = value; \
    at->prev->next = item; \
    item->prev = at->prev; \
    at->prev = item; \
    item->next = at; \
    ++deque->size; \
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
    size_t i; \
    struct _CSSOM_DequeItem_##suffix *item; \
    \
    for (i = 0, item = deque->head->next; i < index; ++i, item = item->next); \
    \
    return (CSSOM_DequeIter_##suffix)item; \
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
