#include "test_FSM.h"

#include <src/FSM.h>

#include <stdlib.h>
#include <assert.h>



void test_FSM_basics() {
  CSSOM_FSMItem *map;
  CSSOM_FSM *fsm;

  map = (CSSOM_FSMItem*)malloc(sizeof(CSSOM_FSMItem) * 3);
  map[0].key = "aaa";
  map[0].value = 0;
  map[1].key = "aab";
  map[1].value = 1;
  map[2].key = NULL;
  map[2].value = 999;

  fsm = CSSOM_FSM_alloc(map);

  assert(CSSOM_FSM_find(fsm, "aaA") == 0);
  assert(CSSOM_FSM_find(fsm, "aaB") == 1);
  assert(CSSOM_FSM_find(fsm, "aaC") == -1);

  assert(CSSOM_FSM_size(fsm) == 2);

  CSSOM_FSM_free(fsm);
  free(map);
}



void test_FSM() {
  test_FSM_basics();
}
