#ifndef _CSSOM_UTILITY_H
#define _CSSOM_UTILITY_H



#define SWAPP(lhs, rhs) \
  do { \
    void *t = (void*)lhs; \
    lhs = rhs; \
    rhs = t; \
  } while (0)

/*
#define SWAP SWAPP
*/



#define SWAPS(lhs, rhs) \
  do { \
    unsigned char temp[sizeof(lhs) == sizeof(rhs) ? (signed)sizeof(lhs) : -1]; \
    memcpy(temp, &rhs, sizeof(lhs)); \
    memcpy(&rhs, &lhs, sizeof(lhs)); \
    memcpy(&lhs, temp, sizeof(lhs)); \
  } while(0)



#endif
