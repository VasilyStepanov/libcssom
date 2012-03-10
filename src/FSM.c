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
  struct _CSSOM_FSMTable_##suffix { \
    const char **map; \
    size_t capacity; \
  }; \
  \
  \
  \
  CSSOM_FSMTable_##suffix* CSSOM_FSMTable_##suffix##_alloc(const char **map) { \
    CSSOM_FSMTable_##suffix *table; \
    size_t capacity; \
    const char **mapit; \
    \
    for (mapit = map, capacity = 0; *mapit != NULL; ++mapit, ++capacity); \
    \
    table = (CSSOM_FSMTable_##suffix*)malloc(sizeof(CSSOM_FSMTable_##suffix)); \
    if (table == NULL) return NULL; \
    \
    table->map = map; \
    table->capacity = capacity; \
    \
    return table; \
  } \
  \
  \
  \
  void CSSOM_FSMTable_##suffix##_free(CSSOM_FSMTable_##suffix *table) { \
    free(table); \
  } \
  \
  \
  \
  static size_t FSMTable_##suffix##_capacity( \
    const CSSOM_FSMTable_##suffix *table) \
  { \
    return table->capacity; \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_find( \
    const CSSOM_FSMTable_##suffix *table, const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = table->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_add( \
    const CSSOM_FSMTable_##suffix *table, const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = table->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_remove( \
    const CSSOM_FSMTable_##suffix *table, const char *key) \
  { \
    const char **it; \
    int index; \
    \
    for (it = table->map, index = 0; *it != NULL; ++it, ++index) { \
      if (strcasecmp(*it, key) == 0) return index; \
    } \
    \
    return -1; \
  } \
  \
  \
  \
  static const char* FSMTable_##suffix##_key( \
    const CSSOM_FSMTable_##suffix *table, size_t hash) \
  { \
    return table->map[hash]; \
  } \
  \
  \
  \
  struct _CSSOM_FSM_##suffix { \
    const CSSOM_FSMTable_##suffix *table; \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
  }; \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc( \
    const CSSOM_FSMTable_##suffix *table) \
  { \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    CSSOM_FSM_##suffix *fsm; \
    CSSOM_VectorIter_FSMItemPtr_##suffix refsit; \
    \
    refs = CSSOM_Vector_FSMItemPtr_##suffix##_alloc( \
      FSMTable_##suffix##_capacity(table)); \
    if (refs == NULL) return NULL; \
    \
    data = CSSOM_Deque_FSMItem_##suffix##_alloc_ex(0, \
      FSMTable_##suffix##_capacity(table)); \
    if (data == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
      return NULL; \
    } \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
      CSSOM_Deque_FSMItem_##suffix##_free(data); \
      return NULL; \
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
    fsm->table = table; \
    fsm->refs = refs; \
    fsm->data = data; \
    \
    return fsm; \
  } \
  \
  \
  \
  void CSSOM_FSM_##suffix##_free(CSSOM_FSM_##suffix *fsm) { \
    CSSOM_Deque_FSMItem_##suffix##_free(fsm->data); \
    CSSOM_Vector_FSMItemPtr_##suffix##_free(fsm->refs); \
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
    hash = FSMTable_##suffix##_find(fsm->table, key); \
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
    hash = FSMTable_##suffix##_add(fsm->table, key); \
    if (hash == -1) return CSSOM_FSM_##suffix##_end(fsm); \
    \
    item.key = FSMTable_##suffix##_key(fsm->table, hash); \
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
    hash = FSMTable_##suffix##_remove(fsm->table, position->key); \
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
