#ifndef _CSSOM_LIST_DEFINE_H
#define _CSSOM_LIST_DEFINE_H

#include "gcc.h"

#include <stdlib.h>



#define CSSOM_LIST_DEFINE(T, suffix) \
  struct _CSSOM_List_##suffixItem { \
    T value; \
    struct _CSSOM_List_##suffixItem *next; \
  }; \
  \
  \
  \
  static struct _CSSOM_List_##suffixItem* CSSOM_List_##suffixItem_alloc() { \
    struct _CSSOM_List_##suffixItem *item; \
    \
    item = (struct _CSSOM_List_##suffixItem*)malloc( \
      sizeof(struct _CSSOM_List_##suffixItem)); \
    if (item == NULL) return NULL; \
    \
    item->next = NULL; \
    return item; \
  } \
  \
  \
  \
  static void CSSOM_List_##suffixItem_free( \
    struct _CSSOM_List_##suffixItem *item) \
  { \
    free(item); \
  } \
  \
  \
  \
  struct _CSSOM_List_##suffix { \
    struct _CSSOM_List_##suffixItem *head; \
    struct _CSSOM_List_##suffixItem *tail; \
    size_t size; \
  }; \
  \
  \
  \
  CSSOM_List_##suffix* CSSOM_List_##suffix##_alloc() { \
    CSSOM_List_##suffix *list; \
    struct _CSSOM_List_##suffixItem *item; \
    \
    item = CSSOM_List_##suffixItem_alloc(); \
    if (item == NULL) return NULL; \
    \
    list = (CSSOM_List_##suffix*)malloc( \
      sizeof(CSSOM_List_##suffix)); \
    if (list == NULL) return NULL; \
    \
    list->head = item; \
    list->tail = list->head; \
    list->size = 0; \
    return list; \
  } \
  \
  \
  \
  void CSSOM_List_##suffix##_free(CSSOM_List_##suffix *list) { \
    struct _CSSOM_List_##suffixItem *item; \
    struct _CSSOM_List_##suffixItem *next; \
    \
    for (item = list->head; item != NULL; item = next) { \
      next = item->next; \
      CSSOM_List_##suffixItem_free(item); \
    } \
    free(list); \
  } \
  \
  \
  \
  T* CSSOM_List_##suffix##_append(CSSOM_List_##suffix *list, T value) { \
    struct _CSSOM_List_##suffixItem *item; \
    \
    item = CSSOM_List_##suffixItem_alloc(); \
    if (item == NULL) return NULL; \
    \
    item->value = value; \
    list->tail->next = item; \
    list->tail = item; \
    ++list->size; \
    return &item->value; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_begin( \
    CSSOM_List_##suffix *list) \
  { \
    return (CSSOM_ListIter_##suffix)list->head->next; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_end( \
    CSSOM_List_##suffix *list CSSOM_UNUSED) \
  { \
    return (CSSOM_ListIter_##suffix)NULL; \
  } \
  \
  \
  \
  size_t CSSOM_List_##suffix##_size(CSSOM_List_##suffix *list) { \
    return list->size; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_ListIter_##suffix##_next( \
    CSSOM_ListIter_##suffix iter) \
  { \
    return (CSSOM_ListIter_##suffix) \
      ((struct _CSSOM_List_##suffixItem*)iter)->next; \
  }



#endif
