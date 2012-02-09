#ifndef GCC_H
#define GCC_H



#if defined(__GNUC__) && (__GNUC__ >= 3)
#  define CSSOM_UNUSED  __attribute__ ((unused))
#else
#  define CSSOM_UNUSED
#endif



#endif
