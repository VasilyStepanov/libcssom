#ifndef CSSOM_LIST_H
#define CSSOM_LIST_H

#include <stdlib.h>



#define CSSOM_LIST_DECLARE(N, T) \
  typedef struct _##N N; \
  \
  N* N##_init(); \
  void N##_free(N *list);



#define CSSOM_LIST_DEFINE(N, T) \
  struct _##N { \
    int dummy; \
  }; \
  \
  \
  \
  N* N##_init() { \
    N *list; \
    \
    list = malloc(sizeof(struct _##N)); \
    return list; \
  } \
  \
  \
  \
  void N##_free(N *list) { \
    free(list); \
  }



#endif
