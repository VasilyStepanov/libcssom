#include "test_FSM.h"

#include "src/FSM.h"
#include "src/FSM.c"

#include <stdlib.h>
#include <assert.h>



CSSOM_FSM_DECLARE(int, Int)

CSSOM_FSM_DEFINE(int, Int)



void test_FSM_basics() {
  const char *map[] = {
    "aaa",
    "aab",
    NULL
  };

  CSSOM_FSM_Int *fsm;

  fsm = CSSOM_FSM_Int_alloc(map);

  assert(CSSOM_FSM_Int_find(fsm, "aaA") == 0);
  assert(CSSOM_FSM_Int_find(fsm, "aaB") == 1);
  assert(CSSOM_FSM_Int_find(fsm, "aaC") == -1);

  assert(CSSOM_FSM_Int_size(fsm) == 2);

  CSSOM_FSM_Int_free(fsm);
}



void test_FSM() {
  test_FSM_basics();
}
