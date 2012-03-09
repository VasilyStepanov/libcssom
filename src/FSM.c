#include "FSM.h"

#include "Vector.h"
#include "Vector.c"
#include "Deque.h"
#include "Deque.c"

#include <stdlib.h>
#include <string.h>
#include <strings.h>



#define CSSOM_FSM_DEFINE(T, suffix) \
  CSSOM_VECTOR_DECLARE(int, FSMItemIdx_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(int, FSMItemIdx_##suffix) \
  \
  CSSOM_VECTOR_DECLARE(CSSOM_FSMItem_##suffix*, FSMItemPtr_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(CSSOM_FSMItem_##suffix*, FSMItemPtr_##suffix) \
  \
  CSSOM_DEQUE_DECLARE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DEFINE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  \
  \
  struct _CSSOM_FSM_##suffix { \
    CSSOM_Vector_FSMItemIdx_##suffix *table; \
    CSSOM_Vector_FSMItemPtr_##suffix *map; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    size_t capacity; \
  }; \
  \
  \
  \
  int CSSOM_FSM_##suffix##_search(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    CSSOM_VectorConstIter_FSMItemIdx_##suffix it; \
    struct _CSSOM_FSMItem_##suffix * const * rawmap = \
      CSSOM_Vector_FSMItemPtr_##suffix##_cbegin(fsm->map); \
    \
    for ( \
      it = CSSOM_Vector_FSMItemIdx_##suffix##_begin(fsm->table); \
      it != CSSOM_Vector_FSMItemIdx_##suffix##_end(fsm->table); \
      it = CSSOM_VectorConstIter_FSMItemIdx_##suffix##_next(it)) \
    { \
      const struct _CSSOM_FSMItem_##suffix *item = rawmap[*it]; \
      if (strcasecmp(item->key, key) == 0) return *it; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc(const char **dict) { \
    CSSOM_Vector_FSMItemIdx_##suffix *table; \
    CSSOM_Vector_FSMItemPtr_##suffix *map; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    CSSOM_FSM_##suffix *fsm; \
    size_t capacity; \
    int i; \
    CSSOM_VectorIter_FSMItemIdx_##suffix tableit; \
    const char **dictit; \
    \
    for (dictit = dict, capacity = 0; *dictit != NULL; ++dictit, ++capacity); \
    \
    table = CSSOM_Vector_FSMItemIdx_##suffix##_alloc(capacity); \
    if (table == NULL) return NULL; \
    \
    map = CSSOM_Vector_FSMItemPtr_##suffix##_alloc(capacity); \
    if (map == NULL) { \
      CSSOM_Vector_FSMItemIdx_##suffix##_free(table); \
      return NULL; \
    } \
    \
    data = CSSOM_Deque_FSMItem_##suffix##_alloc_ex(0, capacity); \
    if (data == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(map); \
      CSSOM_Vector_FSMItemIdx_##suffix##_free(table); \
      return NULL; \
    } \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(map); \
      CSSOM_Vector_FSMItemIdx_##suffix##_free(table); \
      CSSOM_Deque_FSMItem_##suffix##_free(data); \
      return NULL; \
    } \
    \
    for ( \
      tableit = CSSOM_Vector_FSMItemIdx_##suffix##_begin(table), i = 0; \
      tableit != CSSOM_Vector_FSMItemIdx_##suffix##_end(table); \
      tableit = CSSOM_VectorIter_FSMItemIdx_##suffix##_next(tableit), ++i) \
    { \
      *tableit = i; \
    } \
    \
    fsm->table = table; \
    fsm->map = map; \
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
    CSSOM_Vector_FSMItemPtr_##suffix##_free(fsm->map); \
    CSSOM_Vector_FSMItemIdx_##suffix##_free(fsm->table); \
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
