#ifndef CSSOM_MEMORY_H
#define CSSOM_MEMORY_H

#include <stdlib.h>
#include <stddef.h>



/*
#define CSSOM_malloc(size) \
  malloc((size))



#define CSSOM_free(ptr) \
  free((ptr))
*/



void * mymalloc(const char * file, int line, size_t size);



void myfree(const char * file, int line, void * ptr);



#define CSSOM_malloc(size) \
  mymalloc(__FILE__, __LINE__, (size))



#define CSSOM_free(ptr) \
  myfree(__FILE__, __LINE__, (ptr))



#endif
