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
  CSSOM_DEQUE_DECLARE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DEFINE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_VECTOR_DECLARE(CSSOM_DequeIter_FSMItem_##suffix, FSMItemPtr_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(CSSOM_DequeIter_FSMItem_##suffix, FSMItemPtr_##suffix) \
  \
  \
  \
  struct _CSSOM_FSM_##suffix { \
    const char **map; \
    CSSOM_Vector_FSMItemIdx_##suffix *table; \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    size_t capacity; \
  }; \
  \
  \
  \
  static int CSSOM_FSM_##suffix##_table_find(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = fsm->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  static int CSSOM_FSM_##suffix##_table_add(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = fsm->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  static int CSSOM_FSM_##suffix##_table_remove(const CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = fsm->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc(const char **map) { \
    CSSOM_Vector_FSMItemIdx_##suffix *table; \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    CSSOM_FSM_##suffix *fsm; \
    size_t capacity; \
    int i; \
    CSSOM_VectorIter_FSMItemIdx_##suffix tableit; \
    CSSOM_VectorIter_FSMItemPtr_##suffix refsit; \
    const char **mapit; \
    \
    for (mapit = map, capacity = 0; *mapit != NULL; ++mapit, ++capacity); \
    \
    table = CSSOM_Vector_FSMItemIdx_##suffix##_alloc(capacity); \
    if (table == NULL) return NULL; \
    \
    refs = CSSOM_Vector_FSMItemPtr_##suffix##_alloc(capacity); \
    if (refs == NULL) { \
      CSSOM_Vector_FSMItemIdx_##suffix##_free(table); \
      return NULL; \
    } \
    \
    data = CSSOM_Deque_FSMItem_##suffix##_alloc_ex(0, capacity); \
    if (data == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
      CSSOM_Vector_FSMItemIdx_##suffix##_free(table); \
      return NULL; \
    } \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
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
    for ( \
      refsit = CSSOM_Vector_FSMItemPtr_##suffix##_begin(refs); \
      refsit != CSSOM_Vector_FSMItemPtr_##suffix##_end(refs); \
      refsit = CSSOM_VectorIter_FSMItemPtr_##suffix##_next(refsit)) \
    { \
      *refsit = CSSOM_Deque_FSMItem_##suffix##_end(data); \
    } \
    \
    fsm->map = map; \
    fsm->table = table; \
    fsm->refs = refs; \
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
    CSSOM_Vector_FSMItemPtr_##suffix##_free(fsm->refs); \
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
  } \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_find(CSSOM_FSM_##suffix *fsm, \
    const char *key) \
  { \
    int hash; \
    CSSOM_VectorIter_FSMItemPtr_##suffix at; \
    \
    hash = CSSOM_FSM_##suffix##_table_find(fsm, key); \
    if (hash == -1) return CSSOM_FSM_##suffix##_end(fsm); \
    \
    at = CSSOM_Vector_FSMItemPtr_##suffix##_begin(fsm->refs) + hash; \
    if (*at == CSSOM_Deque_FSMItem_##suffix##_end(fsm->data)) \
      return CSSOM_FSM_##suffix##_end(fsm); \
    \
    return (CSSOM_FSMIter_##suffix)*at; \
  } \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_add(CSSOM_FSM_##suffix *fsm, \
    const char *key, T value) \
  { \
    CSSOM_FSMItem_##suffix item; \
    int hash; \
    CSSOM_VectorIter_FSMItemPtr_##suffix at; \
    CSSOM_DequeIter_FSMItem_##suffix itemit; \
    \
    hash = CSSOM_FSM_##suffix##_table_add(fsm, key); \
    if (hash == -1) return CSSOM_FSM_##suffix##_end(fsm); \
    \
    item.key = fsm->map[hash]; \
    item.hash = hash; \
    item.value = value; \
    \
    itemit = CSSOM_Deque_FSMItem_##suffix##_append(fsm->data, item); \
    if (itemit == CSSOM_Deque_FSMItem_##suffix##_end(fsm->data)) \
      return CSSOM_FSM_##suffix##_end(fsm); \
    \
    at = CSSOM_Vector_FSMItemPtr_##suffix##_begin(fsm->refs) + hash; \
    if (*at != CSSOM_Deque_FSMItem_##suffix##_end(fsm->data)) \
      CSSOM_Deque_FSMItem_##suffix##_erase(fsm->data, *at); \
    \
    *at = itemit; \
    \
    return (CSSOM_FSMIter_##suffix)itemit; \
  } \
  \
  \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_erase(CSSOM_FSM_##suffix *fsm, \
    CSSOM_FSMIter_##suffix position) \
  { \
    int hash; \
    CSSOM_VectorIter_FSMItemPtr_##suffix at; \
    CSSOM_DequeIter_FSMItem_##suffix erase; \
    \
    hash = CSSOM_FSM_##suffix##_table_remove(fsm, position->key); \
    if (hash == -1) return CSSOM_FSM_##suffix##_end(fsm); \
    \
    at = CSSOM_Vector_FSMItemPtr_##suffix##_begin(fsm->refs) + hash; \
    \
    erase = *at; \
    *at = CSSOM_Deque_FSMItem_##suffix##_end(fsm->data); \
    \
    return (CSSOM_FSMIter_##suffix) \
      CSSOM_Deque_FSMItem_##suffix##_erase(fsm->data, erase); \
  }
