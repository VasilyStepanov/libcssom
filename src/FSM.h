#ifndef CSSOM_FSM_H
#define CSSOM_FSM_H

#include <stddef.h>



#define CSSOM_FSM_DECLARE(T, suffix) \
  typedef struct _CSSOM_FSM_##suffix CSSOM_FSM_##suffix; \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc(const char **map); \
  void CSSOM_FSM_##suffix##_free(CSSOM_FSM_##suffix *fsm); \
  int CSSOM_FSM_##suffix##_find(const CSSOM_FSM_##suffix *fsm, \
    const char *key); \
  size_t CSSOM_FSM_##suffix##_size(const CSSOM_FSM_##suffix *fsm);



#endif
