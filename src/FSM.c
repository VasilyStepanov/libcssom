#include "FSM.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



struct _CSSOM_FSM {
  const CSSOM_FSMItem *map;
  size_t size;
};



CSSOM_FSM* CSSOM_FSM_alloc(const CSSOM_FSMItem *map) {
  CSSOM_FSM *fsm;
  const CSSOM_FSMItem *it;
  int max;

  max = 0;
  for (it = map; it->key != NULL; ++it) {
    if (max < it->value) max = it->value;
  }

  fsm = (CSSOM_FSM*)malloc(sizeof(CSSOM_FSM));
  if (fsm == NULL) return NULL;

  fsm->map = map;
  fsm->size = max + 1;

  return fsm;
}



void CSSOM_FSM_free(CSSOM_FSM *fsm) {
  free(fsm);
}



int CSSOM_FSM_find(const CSSOM_FSM *fsm, const char *key) {
  const CSSOM_FSMItem *it;

  it = fsm->map;
  while (1) {
    if (it->key == NULL) return -1;
    if (strcasecmp(it->key, key) == 0) return it->value;
    ++it;
  }
  
  return -1;
}



size_t CSSOM_FSM_size(const CSSOM_FSM *fsm) {
  return fsm->size;
}
