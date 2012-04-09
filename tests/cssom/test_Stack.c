#include "test_List.h"

#include "src/Stack.h"
#include "src/Stack.c"

#include <assert.h>



CSSOM_STACK_DECLARE(int, Int)

CSSOM_STACK_DEFINE(int, Int)



static void test_Stack_basics(void) {
  CSSOM_Stack_Int *stack;
  int *p;

  stack = CSSOM_Stack_Int_alloc();

  assert(CSSOM_Stack_Int_top(stack) == NULL);
  assert(CSSOM_Stack_Int_ctop(stack) == NULL);



  p = CSSOM_Stack_Int_push(stack, 1);
  assert(p != NULL);
  assert(*p == 1);

  p = CSSOM_Stack_Int_push(stack, 2);
  assert(p != NULL);
  assert(*p == 2);

  p = CSSOM_Stack_Int_push(stack, 3);
  assert(p != NULL);
  assert(*p == 3);



  assert(CSSOM_Stack_Int_top(stack) != NULL);
  assert(*CSSOM_Stack_Int_top(stack) == 3);
  assert(*CSSOM_Stack_Int_ctop(stack) == 3);

  CSSOM_Stack_Int_pop(stack);
  assert(CSSOM_Stack_Int_top(stack) != NULL);
  assert(*CSSOM_Stack_Int_top(stack) == 2);
  assert(*CSSOM_Stack_Int_ctop(stack) == 2);

  CSSOM_Stack_Int_pop(stack);
  assert(CSSOM_Stack_Int_top(stack) != NULL);
  assert(*CSSOM_Stack_Int_top(stack) == 1);
  assert(*CSSOM_Stack_Int_ctop(stack) == 1);

  CSSOM_Stack_Int_pop(stack);
  assert(CSSOM_Stack_Int_top(stack) == NULL);
  assert(CSSOM_Stack_Int_ctop(stack) == NULL);



  CSSOM_Stack_Int_free(stack);
}



void test_Stack(void) {
  test_Stack_basics();
}
