#ifndef _CSSOM_LIST_DECLARE_H
#define _CSSOM_LIST_DECLARE_H



#define CSSOM_LIST_DECLARE(T, suffix) \
  typedef struct _CSSOM_List_##suffix CSSOM_List_##suffix; \
  typedef T* CSSOM_ListIter_##suffix; \
  \
  CSSOM_List_##suffix* CSSOM_List_##suffix##_alloc(); \
  void CSSOM_List_##suffix##_free(CSSOM_List_##suffix *list); \
  T* CSSOM_List_##suffix##_append(CSSOM_List_##suffix *list, T value); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_begin( \
    CSSOM_List_##suffix *list); \
  CSSOM_ListIter_##suffix CSSOM_List_##suffix##_end( \
    CSSOM_List_##suffix *list); \
  \
  CSSOM_ListIter_##suffix CSSOM_ListIter_##suffix##_next( \
    CSSOM_ListIter_##suffix iter);



#endif
