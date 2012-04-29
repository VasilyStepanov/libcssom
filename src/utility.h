#ifndef _CSSOM_UTILITY_H
#define _CSSOM_UTILITY_H



#define SWAP(lhs, rhs) \
  do { \
    void *t = (void*)lhs; \
    lhs = rhs; \
    rhs = t; \
  } while (0)



#endif
