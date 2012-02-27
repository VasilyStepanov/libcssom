#include "test_FSM.h"

#include <src/FSM.h>

#include <stdlib.h>
#include <assert.h>



void test_FSM_basics() {
  CSSOM_FSMItem map[] = {
    {"aaa", 0},
    {"aab", 1},
    {NULL, 999}
  };

  CSSOM_FSM *fsm;

  fsm = CSSOM_FSM_alloc(map);

  assert(CSSOM_FSM_find(fsm, "aaA") == 0);
  assert(CSSOM_FSM_find(fsm, "aaB") == 1);
  assert(CSSOM_FSM_find(fsm, "aaC") == -1);

  assert(CSSOM_FSM_size(fsm) == 2);

  CSSOM_FSM_free(fsm);
}



void test_FSM() {
  test_FSM_basics();
}
