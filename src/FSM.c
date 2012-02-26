#include "FSM.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



struct _CSSOM_FSM {
  CSSOM_FSMItem *map;
};



CSSOM_FSM* CSSOM_FSM_alloc(CSSOM_FSMItem *map) {
  CSSOM_FSM *fsm;

  fsm = (CSSOM_FSM*)malloc(sizeof(CSSOM_FSM));
  if (fsm == NULL) return NULL;

  fsm->map = map;

  return fsm;
}



void CSSOM_FSM_free(CSSOM_FSM *fsm) {
  free(fsm);
}



int CSSOM_FSM_find(const CSSOM_FSM *fsm, const char *key) {
  CSSOM_FSMItem *it;

  it = fsm->map;
  while (1) {
    if (it->key == NULL) return it->value;
    if (strcasecmp(it->key, key) == 0) return it->value;
    ++it;
  }
  
  return -1;
}
