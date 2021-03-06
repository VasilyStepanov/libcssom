#include "List.h"

#include "memory.h"



#define CSSOM_LIST_DEFINE(T, suffix) \
  struct _CSSOM_ListItem_##suffix { \
    T value; \
    struct _CSSOM_ListItem_##suffix *prev; \
    struct _CSSOM_ListItem_##suffix *next; \
  }; \
  \
  \
  \
  static struct _CSSOM_ListItem_##suffix* ListItem_##suffix##_alloc(void) { \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = (struct _CSSOM_ListItem_##suffix*)CSSOM_malloc( \
      sizeof(struct _CSSOM_ListItem_##suffix)); \
    if (item == NULL) return NULL; \
    \
    item->next = NULL; \
    item->prev = NULL; \
    \
    return item; \
  } \
  \
  \
  \
  static void ListItem_##suffix##_free( \
    struct _CSSOM_ListItem_##suffix *item) \
  { \
    CSSOM_free(item); \
  } \
  \
  \
  \
  static void ListItem_##suffix##_freeAll( \
    struct _CSSOM_ListItem_##suffix *item) \
  { \
    struct _CSSOM_ListItem_##suffix *next; \
    \
    for (; item != NULL; item = next) { \
      next = item->next; \
      ListItem_##suffix##_free(item); \
    } \
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
  CSSOM_List_##suffix* CSSOM_List_##suffix##_alloc(void) { \
    CSSOM_List_##suffix *list; \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = ListItem_##suffix##_alloc(); \
    if (item == NULL) return NULL; \
    \
    list = (CSSOM_List_##suffix*)CSSOM_malloc( \
      sizeof(CSSOM_List_##suffix)); \
    if (list == NULL) { \
      ListItem_##suffix##_free(item); \
      return NULL; \
    } \
    \
    list->head = item; \
    list->tail = item; \
    list->size = 0; \
    \
    return list; \
  } \
  \
  \
  \
  void CSSOM_List_##suffix##_free(CSSOM_List_##suffix *list) { \
    ListItem_##suffix##_freeAll(list->head); \
    CSSOM_free(list); \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix  CSSOM_List_##suffix##_append( \
    CSSOM_List_##suffix *list, T value) \
  { \
    struct _CSSOM_ListItem_##suffix *item; \
    \
    item = ListItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_List_##suffix##_end(list); \
    \
    item->value = value; \
    item->prev = list->tail; \
    list->tail->next = item; \
    list->tail = item; \
    ++list->size; \
    \
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
    item = ListItem_##suffix##_alloc(); \
    if (item == NULL) return CSSOM_List_##suffix##_end(list); \
    \
    item->value = value; \
    at->prev->next = item; \
    item->prev = at->prev; \
    at->prev = item; \
    item->next = at; \
    ++list->size; \
    \
    return (CSSOM_ListIter_##suffix)item; \
  } \
  \
  \
  \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_erase( \
    CSSOM_List_##suffix *list, CSSOM_ListIter_##suffix position) \
  { \
    struct _CSSOM_ListItem_##suffix *item; \
    struct _CSSOM_ListItem_##suffix *at; \
    \
    at = (struct _CSSOM_ListItem_##suffix*)position; \
    item = at->next; \
    \
    at->prev->next = item; \
    if (item != NULL) item->prev = at->prev; \
    ListItem_##suffix##_free(at); \
    --list->size; \
    \
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
    CSSOM_List_##suffix *list) \
  { \
    return (CSSOM_ListIter_##suffix)list->tail->next; \
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
    const CSSOM_List_##suffix *list) \
  { \
    return (CSSOM_ListConstIter_##suffix)list->tail->next; \
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
