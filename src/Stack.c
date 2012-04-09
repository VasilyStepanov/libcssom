#include "Stack.h"

#include "memory.h"



#define CSSOM_STACK_DEFINE(T, suffix) \
  struct _CSSOM_StackItem_##suffix { \
    T value; \
    struct _CSSOM_StackItem_##suffix *prev; \
  }; \
  \
  \
  \
  static struct _CSSOM_StackItem_##suffix* StackItem_##suffix##_alloc( \
    T value, struct _CSSOM_StackItem_##suffix *prev) \
  { \
    struct _CSSOM_StackItem_##suffix *item; \
    \
    item = (struct _CSSOM_StackItem_##suffix*)CSSOM_malloc( \
      sizeof(struct _CSSOM_StackItem_##suffix)); \
    if (item == NULL) return NULL; \
    \
    item->value = value; \
    item->prev = prev; \
    \
    return item; \
  } \
  \
  \
  \
  static void StackItem_##suffix##_free( \
    struct _CSSOM_StackItem_##suffix *item) \
  { \
    CSSOM_free(item); \
  } \
  \
  \
  \
  struct _CSSOM_Stack_##suffix { \
    T *head; \
  }; \
  \
  \
  \
  CSSOM_Stack_##suffix* CSSOM_Stack_##suffix##_alloc(void) { \
    CSSOM_Stack_##suffix *stack; \
    \
    stack = (CSSOM_Stack_##suffix*)CSSOM_malloc(sizeof(CSSOM_Stack_##suffix)); \
    if (stack == NULL) return NULL; \
    \
    stack->head = NULL; \
    \
    return stack; \
  } \
  \
  \
  \
  void CSSOM_Stack_##suffix##_free(CSSOM_Stack_##suffix *stack) { \
    CSSOM_free(stack); \
  } \
  \
  \
  \
  T* CSSOM_Stack_##suffix##_top(CSSOM_Stack_##suffix *stack) { \
    return stack->head; \
  } \
  \
  \
  \
  const T* CSSOM_Stack_##suffix##_ctop(const CSSOM_Stack_##suffix *stack) { \
    return stack->head; \
  } \
  \
  \
  \
  T* CSSOM_Stack_##suffix##_push(CSSOM_Stack_##suffix *stack, T value) { \
    struct _CSSOM_StackItem_##suffix *head; \
    \
    head = StackItem_##suffix##_alloc(value, \
      (struct _CSSOM_StackItem_##suffix*)stack->head); \
    if (head == NULL) return NULL; \
    \
    stack->head = (T*)head; \
    \
    return stack->head; \
  } \
  \
  \
  \
  void CSSOM_Stack_##suffix##_pop(CSSOM_Stack_##suffix *stack) { \
    struct _CSSOM_StackItem_##suffix *head; \
    \
    head = (struct _CSSOM_StackItem_##suffix*)stack->head; \
    stack->head = (T*)head->prev; \
    StackItem_##suffix##_free(head); \
  }
