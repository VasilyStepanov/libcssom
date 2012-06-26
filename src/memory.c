#include "memory.h"

#include "gcc.h"

#include <stdio.h>
#include <stdlib.h>

/* #define _CSSOM_DETAILED */


static void dumpMalloc(const char * file, int line CSSOM_UNUSED,
  const char * function CSSOM_UNUSED, void * ptr)
{
  FILE * f;
  f = fopen("malloc", "a");
#ifndef _CSSOM_DETAILED
  fprintf(f, "%x %s\n", (int)ptr, file);
#else
  fprintf(f, "%x %s %d\n", (int)ptr, file, line);
#endif
  fclose(f);
}



static void dumpFree(const char * file, int line CSSOM_UNUSED,
  const char * function CSSOM_UNUSED, void * ptr)
{
  FILE * f;

  if (ptr != NULL) {
    f = fopen("free", "a");
#ifndef _CSSOM_DETAILED
    fprintf(f, "%x %s\n", (int)ptr, file);
#else
    fprintf(f, "%x %s %d\n", (int)ptr, file, line);
#endif
    fclose(f);
  }
}



void * _CSSOM_mymalloc(const char * file, int line, const char * function,
  size_t size)
{
  void * ptr = malloc(size);
  dumpMalloc(file, line, function, ptr);
  return ptr;
}



void * _CSSOM_myrealloc(const char * file, int line, const char * function,
  void * ptr, size_t size)
{
  dumpFree(file, line, function, ptr);
  ptr = realloc(ptr, size);
  dumpMalloc(file, line, function, ptr);
  return ptr;
}



void _CSSOM_myfree(const char * file, int line, const char * function,
  void * ptr)
{
  dumpFree(file, line, function, ptr);
  free(ptr);
}
