#ifndef CSSOM_SEQUENCE_IMPL_H
#define CSSOM_SEQUENCE_IMPL_H

#include <stdlib.h>



#define CSSOM_SEQUENCE_IMPL(name, type) \
  struct _##name { \
    int dummy; \
  }; \
  \
  void name##_free(name *sequence) { \
    free(sequence); \
  }



#endif
