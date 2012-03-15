#ifndef _CSSOM_LIST_H
#define _CSSOM_LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_LIST_DECLARE(T, suffix) \
  typedef struct _CSSOM_List_##suffix CSSOM_List_##suffix; \
  typedef T* CSSOM_ListIter_##suffix; \
  typedef T const * CSSOM_ListConstIter_##suffix; \
  \
  CSSOM_List_##suffix* CSSOM_List_##suffix##_alloc(); \
  void CSSOM_List_##suffix##_free(CSSOM_List_##suffix *list); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_append( \
    CSSOM_List_##suffix *list, T value); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_insert( \
    CSSOM_List_##suffix *list, CSSOM_ListIter_##suffix position, T value); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_erase( \
    CSSOM_List_##suffix *list, CSSOM_ListIter_##suffix position); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_begin( \
    CSSOM_List_##suffix *list); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_end( \
    CSSOM_List_##suffix *list); \
  CSSOM_ListConstIter_##suffix CSSOM_List_##suffix##_cbegin( \
    const CSSOM_List_##suffix *list); \
  CSSOM_ListConstIter_##suffix CSSOM_List_##suffix##_cend( \
    const CSSOM_List_##suffix *list); \
  size_t CSSOM_List_##suffix##_size(const CSSOM_List_##suffix *list); \
  \
  CSSOM_ListIter_##suffix CSSOM_ListIter_##suffix##_next( \
    CSSOM_ListIter_##suffix iter); \
  CSSOM_ListConstIter_##suffix CSSOM_ListConstIter_##suffix##_next( \
    CSSOM_ListConstIter_##suffix iter);



#ifdef __cplusplus
}
#endif

#endif
