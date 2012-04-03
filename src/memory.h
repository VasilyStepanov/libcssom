#ifndef CSSOM_MEMORY_H
#define CSSOM_MEMORY_H

#include "config.h"

#include <stdlib.h>
#include <stddef.h>



#ifndef ENABLE_MEMORY_TRACE



# define CSSOM_malloc(size) \
    malloc((size))

# define CSSOM_realloc(ptr, size) \
    realloc((ptr), (size))

#define CSSOM_free(ptr) \
  free((ptr))

#define CSSOM_native_free(ptr) \
  free((ptr))



#else



void * _CSSOM_mymalloc(const char * file, int line, const char * function,
  size_t size);

void * _CSSOM_myrealloc(const char * file, int line, const char * function,
  void * ptr, size_t size);

void _CSSOM_myfree(const char * file, int line, const char * function,
  void * ptr);

# define CSSOM_malloc(size) \
    _CSSOM_mymalloc(__FILE__, __LINE__, __FUNCTION__, (size))

# define CSSOM_realloc(ptr, size) \
    _CSSOM_myrealloc(__FILE__, __LINE__, __FUNCTION__, (ptr), (size))

# define CSSOM_free(ptr) \
    _CSSOM_myfree(__FILE__, __LINE__, __FUNCTION__, (ptr))

# define CSSOM_native_free(ptr) \
    free((ptr))



#endif



#endif
