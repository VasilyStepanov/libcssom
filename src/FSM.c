#include "FSM.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



#define CSSOM_FSM_DEFINE(T, suffix) \
  struct _CSSOM_FSM_##suffix { \
    const char **map; \
    size_t size; \
  }; \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc(const char **map) { \
    CSSOM_FSM_##suffix *fsm; \
    size_t size; \
    const char **it; \
    \
    for (it = map, size = 0; *it != NULL; ++it, ++size); \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) return NULL; \
    \
    fsm->map = map; \
    fsm->size = size; \
    \
    return fsm; \
  } \
  \
  \
  \
  void CSSOM_FSM_##suffix##_free(CSSOM_FSM_##suffix *fsm) { \
    free(fsm); \
  } \
  \
  \
  \
  int CSSOM_FSM_##suffix##_find(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    size_t i; \
    const char **it; \
    \
    for (i = 0, it = fsm->map; i < fsm->size; ++i, ++it) \
      if (strcasecmp(*it, key) == 0) return i; \
    \
    return -1; \
  } \
  \
  \
  \
  size_t CSSOM_FSM_##suffix##_size(const CSSOM_FSM_##suffix *fsm) { \
    return fsm->size; \
  }
