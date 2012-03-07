#include "FSM.h"

#include "Vector.h"
#include "Vector.c"
#include "Deque.h"
#include "Deque.c"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



#define CSSOM_FSM_DEFINE(T, suffix) \
  CSSOM_VECTOR_DECLARE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DECLARE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DEFINE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  \
  \
  struct _CSSOM_FSM_##suffix { \
    CSSOM_Vector_FSMItem_##suffix *table; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    size_t capacity; \
  }; \
  \
  \
  \
  int CSSOM_FSM_##suffix##_search(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    CSSOM_VectorConstIter_FSMItem_##suffix it; \
    \
    for ( \
      it = CSSOM_Vector_FSMItem_##suffix##_begin(fsm->table); \
      it != CSSOM_Vector_FSMItem_##suffix##_end(fsm->table); \
      it = CSSOM_VectorConstIter_FSMItem_##suffix##_next(it)) \
    { \
      if (strcasecmp(it->key, key) == 0) return it->hash; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc(const char **map) { \
    CSSOM_Deque_FSMItem_##suffix *data; \
    CSSOM_Vector_FSMItem_##suffix *table; \
    CSSOM_FSMItem_##suffix *tableraw; \
    CSSOM_FSM_##suffix *fsm; \
    size_t capacity; \
    int i; \
    const char **it; \
    \
    for (it = map, capacity = 0; *it != NULL; ++it, ++capacity); \
    \
    table = CSSOM_Vector_FSMItem_##suffix##_alloc(capacity); \
    if (table == NULL) return NULL; \
    \
    data = CSSOM_Deque_FSMItem_##suffix##_alloc_ex(0, capacity); \
    if (data == NULL) { \
      CSSOM_Vector_FSMItem_##suffix##_free(table); \
      return NULL; \
    } \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) { \
      CSSOM_Deque_FSMItem_##suffix##_free(data); \
      CSSOM_Vector_FSMItem_##suffix##_free(table); \
      return NULL; \
    } \
    \
    tableraw = CSSOM_Vector_FSMItem_##suffix##_begin(table); \
    for (it = map, i = 0; *it != NULL; ++it) { \
      tableraw[i].key = *it; \
      tableraw[i].hash = i; \
    } \
    \
    fsm->table = table; \
    fsm->data = data; \
    fsm->capacity = capacity; \
    \
    return fsm; \
  } \
  \
  \
  \
  void CSSOM_FSM_##suffix##_free(CSSOM_FSM_##suffix *fsm) { \
    CSSOM_Deque_FSMItem_##suffix##_free(fsm->data); \
    CSSOM_Vector_FSMItem_##suffix##_free(fsm->table); \
    free(fsm); \
  } \
  \
  \
  \
  size_t CSSOM_FSM_##suffix##_size(const CSSOM_FSM_##suffix *fsm) { \
    return CSSOM_Deque_FSMItem_##suffix##_size(fsm->data); \
  }  \
  \
  \
  size_t CSSOM_FSM_##suffix##_capacity(const CSSOM_FSM_##suffix *fsm) { \
    return fsm->capacity; \
  } \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_begin(CSSOM_FSM_##suffix *fsm) { \
    return CSSOM_Deque_FSMItem_##suffix##_begin(fsm->data); \
  } \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_end(CSSOM_FSM_##suffix *fsm) { \
    return CSSOM_Deque_FSMItem_##suffix##_end(fsm->data); \
  }  \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSMIter_##suffix##_next( \
    CSSOM_FSMIter_##suffix iter) \
  { \
    return CSSOM_DequeIter_FSMItem_##suffix##_next( \
      (CSSOM_DequeIter_FSMItem_##suffix)iter); \
  }

/*
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSMIter_##suffix##_add(CSSOM_FSM_##suffix *fsm, \
    const char *key, T value) \
  { \
    CSSOM_FSMIter_##suffix match; \
    \
    match = CSSOM_FSM_##suffix##_find(fsm, key); \
    if (match != CSSOM_FSM_##suffix##_end(fsm)) \
      CSSOM_FSM_##suffix##_erase(fsm, match); \
    \
    return CSSOM_FSM_##suffix##_end(fsm); \
  }
*/
