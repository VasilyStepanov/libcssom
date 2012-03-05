#include "FSM.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



struct _CSSOM_FSM {
  const char **map;
  size_t size;
};



CSSOM_FSM* CSSOM_FSM_alloc(const char **map) {
  CSSOM_FSM *fsm;
  size_t size;
  const char **it;

  for (it = map, size = 0; *it != NULL; ++it, ++size);

  fsm = (CSSOM_FSM*)malloc(sizeof(CSSOM_FSM));
  if (fsm == NULL) return NULL;

  fsm->map = map;
  fsm->size = size;

  return fsm;
}



void CSSOM_FSM_free(CSSOM_FSM *fsm) {
  free(fsm);
}



int CSSOM_FSM_find(const CSSOM_FSM *fsm, const char *key) {
  size_t i;
  const char **it;

  for (i = 0, it = fsm->map; i < fsm->size; ++i, ++it)
    if (strcasecmp(*it, key) == 0) return i;
  
  return -1;
}



size_t CSSOM_FSM_size(const CSSOM_FSM *fsm) {
  return fsm->size;
}
