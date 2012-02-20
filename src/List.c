#include "gcc.h"

#include <stdlib.h>



#define CSSOM_LIST_DEFINE(T, suffix) \
  struct _CSSOM_ListItem_##suffix { \
    T value; \
    struct _CSSOM_ListItem_##suffix *prev; \
    struct _CSSOM_ListItem_##suffix *next; \
  }; \
  \
  \
  \
  static struct _CSSOM_ListItem_##suffix* CSSOM_ListItem_##suffix##_alloc() { \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = (struct _CSSOM_ListItem_##suffix*)malloc( \
      sizeof(struct _CSSOM_ListItem_##suffix)); \
    if (item == NULL) return NULL; \
    \
    item->next = NULL; \
    item->prev = NULL; \
    return item; \
  } \
  \
  \
  \
  static void CSSOM_ListItem_##suffix##_free( \
    struct _CSSOM_ListItem_##suffix *item) \
  { \
    free(item); \
  } \
  \
  \
  \
  struct _CSSOM_List_##suffix { \
    struct _CSSOM_ListItem_##suffix *head; \
    struct _CSSOM_ListItem_##suffix *tail; \
    size_t size; \
  }; \
  \
  \
  \
  CSSOM_List_##suffix* CSSOM_List_##suffix##_alloc() { \
    CSSOM_List_##suffix *list; \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = CSSOM_ListItem_##suffix##_alloc(); \
    if (item == NULL) return NULL; \
    \
    list = (CSSOM_List_##suffix*)malloc( \
      sizeof(CSSOM_List_##suffix)); \
    if (list == NULL) { \
      CSSOM_ListItem_##suffix##_free(item); \
      return NULL; \
    } \
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
    struct _CSSOM_ListItem_##suffix *item; \
    struct _CSSOM_ListItem_##suffix *next; \
    \
    for (item = list->head; item != NULL; item = next) { \
      next = item->next; \
      CSSOM_ListItem_##suffix##_free(item); \
    } \
    free(list); \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix  CSSOM_List_##suffix##_append( \
    CSSOM_List_##suffix *list, T value) \
  { \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = CSSOM_ListItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_List_##suffix##_end(list); \
    \
    item->value = value; \
    item->prev = list->tail; \
    list->tail->next = item; \
    list->tail = item; \
    ++list->size; \
    return (CSSOM_ListIter_##suffix)item; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_insert( \
    CSSOM_List_##suffix *list, CSSOM_ListIter_##suffix position, T value) \
  { \
    struct _CSSOM_ListItem_##suffix *item; \
    struct _CSSOM_ListItem_##suffix *at; \
    \
    if (position == CSSOM_List_##suffix##_end(list)) \
      return CSSOM_List_##suffix##_append(list, value); \
    \
    at = (struct _CSSOM_ListItem_##suffix*)position; \
    item = CSSOM_ListItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_List_##suffix##_end(list); \
    \
    item->value = value; \
    at->prev->next = item; \
    item->prev = at->prev; \
    at->prev = item; \
    item->next = at; \
    ++list->size; \
    return (CSSOM_ListIter_##suffix)item; \
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
  CSSOM_ListConstIter_##suffix CSSOM_List_##suffix##_cbegin( \
    const CSSOM_List_##suffix *list) \
  { \
    return (CSSOM_ListConstIter_##suffix)list->head->next; \
  } \
  \
  \
  \
  CSSOM_ListConstIter_##suffix CSSOM_List_##suffix##_cend( \
    const CSSOM_List_##suffix *list CSSOM_UNUSED) \
  { \
    return (CSSOM_ListConstIter_##suffix)NULL; \
  } \
  \
  \
  \
  size_t CSSOM_List_##suffix##_size(const CSSOM_List_##suffix *list) { \
    return list->size; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_ListIter_##suffix##_next( \
    CSSOM_ListIter_##suffix iter) \
  { \
    return (CSSOM_ListIter_##suffix) \
      ((struct _CSSOM_ListItem_##suffix*)iter)->next; \
  } \
  \
  \
  \
  CSSOM_ListConstIter_##suffix CSSOM_ListConstIter_##suffix##_next( \
    CSSOM_ListConstIter_##suffix iter) \
  { \
    return (CSSOM_ListConstIter_##suffix) \
      ((const struct _CSSOM_ListItem_##suffix*)iter)->next; \
  }
