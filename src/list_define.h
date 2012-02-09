#ifndef CSSOM_LIST_DEFINE_H
#define CSSOM_LIST_DEFINE_H

#include "gcc.h"

#include <stdlib.h>



#define CSSOM_LIST_DEFINE(T, prefix) \
  struct _CSSOM_##prefix##ListItem { \
    T value; \
    struct _CSSOM_##prefix##ListItem *next; \
  }; \
  \
  \
  \
  static struct _CSSOM_##prefix##ListItem* CSSOM_##prefix##ListItem_alloc() { \
    struct _CSSOM_##prefix##ListItem *item; \
    \
    item = (struct _CSSOM_##prefix##ListItem*)malloc( \
      sizeof(struct _CSSOM_##prefix##ListItem)); \
    if (item == NULL) return NULL; \
    \
    item->next = NULL; \
    return item; \
  } \
  \
  \
  \
  static void CSSOM_##prefix##ListItem_free( \
    struct _CSSOM_##prefix##ListItem *item) \
  { \
    free(item); \
  } \
  \
  \
  \
  struct _CSSOM_##prefix##List { \
    struct _CSSOM_##prefix##ListItem *head; \
    struct _CSSOM_##prefix##ListItem *tail; \
    size_t size; \
  }; \
  \
  \
  \
  CSSOM_##prefix##List* CSSOM_##prefix##List_alloc() { \
    CSSOM_##prefix##List *list; \
    struct _CSSOM_##prefix##ListItem *item; \
    \
    item = CSSOM_##prefix##ListItem_alloc(); \
    if (item == NULL) return NULL; \
    \
    list = (CSSOM_##prefix##List*)malloc( \
      sizeof(struct _CSSOM_##prefix##List)); \
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
  void CSSOM_##prefix##List_free(CSSOM_##prefix##List *list) { \
    struct _CSSOM_##prefix##ListItem *item; \
    struct _CSSOM_##prefix##ListItem *next; \
    \
    for (item = list->head; item != NULL; item = next) { \
      next = item->next; \
      CSSOM_##prefix##ListItem_free(item); \
    } \
    free(list); \
  } \
  \
  \
  \
  T* CSSOM_##prefix##List_append(CSSOM_##prefix##List *list, T value) { \
    struct _CSSOM_##prefix##ListItem *item; \
    \
    item = CSSOM_##prefix##ListItem_alloc(); \
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
  CSSOM_##prefix##ListIter CSSOM_##prefix##List_begin( \
    CSSOM_##prefix##List *list) \
  { \
    return (CSSOM_##prefix##ListIter)list->head->next; \
  } \
  \
  \
  \
  CSSOM_##prefix##ListIter CSSOM_##prefix##List_end( \
    CSSOM_##prefix##List *list CSSOM_UNUSED) \
  { \
    return (CSSOM_##prefix##ListIter)NULL; \
  } \
  \
  \
  \
  size_t CSSOM_##prefix##List_size(CSSOM_##prefix##List *list) { \
    return list->size; \
  } \
  \
  \
  \
  CSSOM_##prefix##ListIter CSSOM_##prefix##ListIter_next( \
    CSSOM_##prefix##ListIter iter) \
  { \
    return (CSSOM_##prefix##ListIter) \
      ((struct _CSSOM_##prefix##ListItem*)iter)->next; \
  }



#endif
