#ifndef _CSSOM_STACK_H
#define _CSSOM_STACK_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_STACK_DECLARE(T, suffix) \
  typedef struct _CSSOM_Stack_##suffix CSSOM_Stack_##suffix; \
  \
  CSSOM_Stack_##suffix* CSSOM_Stack_##suffix##_alloc(void); \
  void CSSOM_Stack_##suffix##_free(CSSOM_Stack_##suffix *stack); \
  T* CSSOM_Stack_##suffix##_push(CSSOM_Stack_##suffix *stack, T value); \
  void CSSOM_Stack_##suffix##_pop(CSSOM_Stack_##suffix *stack); \
  T* CSSOM_Stack_##suffix##_top(CSSOM_Stack_##suffix *stack); \
  const T* CSSOM_Stack_##suffix##_ctop(const CSSOM_Stack_##suffix *stack);



#ifdef __cplusplus
}
#endif

#endif
