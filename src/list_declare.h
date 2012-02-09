#ifndef CSSOM_LIST_DECLARE_H
#define CSSOM_LIST_DECLARE_H



#define CSSOM_LIST_DECLARE(N, T) \
  typedef struct _##N N; \
  \
  N* N##_init(); \
  void N##_free(N *list);



#endif
