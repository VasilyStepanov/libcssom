#ifndef CSSOM_SEQUENCE_DEFINE_H
#define CSSOM_SEQUENCE_DEFINE_H

#include <stdlib.h>



#define CSSOM_SEQUENCE_DEFINE(N, T) \
  struct _##N { \
    int dummy; \
  }; \
  \
  \
  \
  N* N##_init() { \
    N *sequence; \
    \
    sequence = malloc(sizeof(struct _##N)); \
    return sequence; \
  } \
  \
  \
  \
  void N##_free(N *sequence) { \
    free(sequence); \
  }



#endif
