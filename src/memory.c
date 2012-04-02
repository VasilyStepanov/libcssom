#include "memory.h"

#include <stdio.h>
#include <stdlib.h>



void * mymalloc(const char * file, int line, size_t size) {
  FILE * f = fopen("malloc", "a");
  void * ptr = malloc(size);
  fprintf(f, "%x %s:%d\n", (int)ptr, file, line);
  fclose(f);
  return ptr;
}



void myfree(const char * file, int line, void * ptr) {
  FILE * f = fopen("free", "a");
  fprintf(f, "%x %s:%d\n", (int)ptr, file, line);
  fclose(f);
  free(ptr);
}
