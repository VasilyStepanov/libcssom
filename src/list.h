#ifndef _CSSOM_LIST_DECLARE_H
#define _CSSOM_LIST_DECLARE_H



#define CSSOM_LIST_DECLARE(T, prefix) \
  typedef struct _CSSOM_##prefix##List CSSOM_##prefix##List; \
  typedef T* CSSOM_##prefix##ListIter; \
  \
  CSSOM_##prefix##List* CSSOM_##prefix##List_alloc(); \
  void CSSOM_##prefix##List_free(CSSOM_##prefix##List *list); \
  T* CSSOM_##prefix##List_append(CSSOM_##prefix##List *list, T value); \
  CSSOM_##prefix##ListIter CSSOM_##prefix##List_begin( \
    CSSOM_##prefix##List *list); \
  CSSOM_##prefix##ListIter CSSOM_##prefix##List_end( \
    CSSOM_##prefix##List *list); \
  \
  CSSOM_##prefix##ListIter CSSOM_##prefix##ListIter_next( \
    CSSOM_##prefix##ListIter iter);



#endif
