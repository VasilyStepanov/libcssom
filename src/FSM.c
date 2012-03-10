#include "FSM.h"

#include "Vector.h"
#include "Vector.c"
#include "Deque.h"
#include "Deque.c"

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>



#define CSSOM_FSM_DEFINE(T, suffix) \
  CSSOM_DEQUE_DECLARE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DEFINE(CSSOM_FSMItem_##suffix, FSMItem_##suffix) \
  \
  CSSOM_DEQUE_DECLARE(int*, FSMTableRow_##suffix) \
  \
  CSSOM_DEQUE_DEFINE(int*, FSMTableRow_##suffix) \
  \
  CSSOM_VECTOR_DECLARE(CSSOM_DequeIter_FSMItem_##suffix, FSMItemPtr_##suffix) \
  \
  CSSOM_VECTOR_DEFINE(CSSOM_DequeIter_FSMItem_##suffix, FSMItemPtr_##suffix) \
  \
  \
  \
  struct _CSSOM_FSMTable_##suffix { \
    const char **map; \
    CSSOM_Deque_FSMTableRow_##suffix *data; \
    size_t amount; \
  }; \
  \
  \
  \
  static CSSOM_DequeIter_FSMTableRow_##suffix FSMTableData_##suffix##_append( \
    CSSOM_Deque_FSMTableRow_##suffix *data) \
  { \
    int *row; \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    row = (int*)malloc(sizeof(int) * 256); \
    if (row == NULL) return CSSOM_Deque_FSMTableRow_##suffix##_end(data); \
    \
    memset(row, 0, sizeof(int) * 256); \
    row[0] = -1; \
    \
    it = CSSOM_Deque_FSMTableRow_##suffix##_append(data, row); \
    if (it == CSSOM_Deque_FSMTableRow_##suffix##_end(data)) \
      return CSSOM_Deque_FSMTableRow_##suffix##_end(data); \
    \
    return it; \
  } \
  \
  \
  \
  static int FSMTableData_##suffix##_add( \
    CSSOM_Deque_FSMTableRow_##suffix *data, const char *key, int hash) \
  { \
    const char *ch; \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    it = CSSOM_Deque_FSMTableRow_##suffix##_begin(data); \
    for (ch = key; *ch != '\0'; ++ch) { \
      int *at; \
      \
      at = &(*it)[(size_t)*ch]; \
      if (*at == 0) { \
        it = FSMTableData_##suffix##_append(data); \
        if (it == CSSOM_Deque_FSMTableRow_##suffix##_end(data)) \
          return -1; \
        \
        *at = CSSOM_Deque_FSMTableRow_##suffix##_size(data) - 1; \
      } else { \
        it = CSSOM_Deque_FSMTableRow_##suffix##_at(data, *at); \
      } \
    } \
    \
    (*it)[0] = hash; \
    \
    return CSSOM_Deque_FSMTableRow_##suffix##_size(data) - 1; \
  } \
  \
  \
  \
  static void FSMTableData_##suffix##_free( \
    CSSOM_Deque_FSMTableRow_##suffix *data) \
  { \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    for ( \
      it = CSSOM_Deque_FSMTableRow_##suffix##_begin(data); \
      it != CSSOM_Deque_FSMTableRow_##suffix##_end(data); \
      it = CSSOM_DequeIter_FSMTableRow_##suffix##_next(it)) \
    { \
      free(*it); \
    } \
    \
    CSSOM_Deque_FSMTableRow_##suffix##_free(data); \
  } \
  \
  \
  \
  static void dump_table(CSSOM_FSMTable_##suffix *table) { \
    const char **mapit; \
    size_t i, j; \
    CSSOM_DequeIter_FSMTableRow_##suffix rowit; \
    \
    for (mapit = table->map, i = 0; *mapit != NULL; ++mapit, ++i) { \
      printf("%3d: %s\n", i, *mapit); \
    } \
    \
    printf("    "); \
    for (j = 0; j < 256; ++j) \
      if ((j >= '0' && j <= '9') \
       || (j >= 'a' && j <= 'z') \
       || (j >= 'A' && j <= 'Z')) \
        printf(" %c", (char)j); \
      else \
        printf("  "); \
    printf("\n"); \
    \
    for ( \
      rowit = CSSOM_Deque_FSMTableRow_##suffix##_begin(table->data), i = 0; \
      rowit != CSSOM_Deque_FSMTableRow_##suffix##_end(table->data); \
      rowit = CSSOM_DequeIter_FSMTableRow_##suffix##_next(rowit), ++i) \
    { \
      printf("%3d:", i); \
      for (j = 0; j < 256; ++j) \
        printf("%2d", (*rowit)[j]); \
      printf("\n"); \
    } \
    printf("\n"); \
    printf("\n"); \
  } \
  \
  \
  \
  CSSOM_FSMTable_##suffix* CSSOM_FSMTable_##suffix##_alloc(const char **map) { \
    CSSOM_Deque_FSMTableRow_##suffix *data; \
    CSSOM_FSMTable_##suffix *table; \
    size_t amount; \
    const char **it; \
    \
    data = CSSOM_Deque_FSMTableRow_##suffix##_alloc(0); \
    if (data == NULL) return NULL; \
    \
    if (FSMTableData_##suffix##_append(data) == \
      CSSOM_Deque_FSMTableRow_##suffix##_end(data)) \
    { \
      FSMTableData_##suffix##_free(data); \
      return NULL; \
    } \
    \
    for (it = map, amount = 0; *it != NULL; ++it, ++amount) { \
      int index; \
      \
      index = FSMTableData_##suffix##_add(data, *it, amount); \
      if (index == -1) { \
        FSMTableData_##suffix##_free(data); \
        return NULL; \
      } \
    } \
    \
    table = (CSSOM_FSMTable_##suffix*)malloc(sizeof(CSSOM_FSMTable_##suffix)); \
    if (table == NULL) { \
      FSMTableData_##suffix##_free(data); \
      return NULL; \
    } \
    \
    table->map = map; \
    table->data = data; \
    table->amount = amount; \
    \
    dump_table(table); \
    \
    return table; \
  } \
  \
  \
  \
  void CSSOM_FSMTable_##suffix##_free(CSSOM_FSMTable_##suffix *table) { \
    FSMTableData_##suffix##_free(table->data); \
    free(table); \
  } \
  \
  \
  \
  static size_t FSMTable_##suffix##_amount( \
    const CSSOM_FSMTable_##suffix *table) \
  { \
    return table->amount; \
  } \
  \
  \
  \
  static size_t FSMTable_##suffix##_size( \
    const CSSOM_FSMTable_##suffix *table) \
  { \
    return CSSOM_Deque_FSMTableRow_##suffix##_size(table->data); \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_find( \
    const CSSOM_FSMTable_##suffix *table, int *state, const char *key) \
  { \
    const char *ch; \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    it = CSSOM_Deque_FSMTableRow_##suffix##_begin(table->data); \
    for (ch = key; *ch != '\0'; ++ch) { \
      int *at; \
      \
      at = &(*it)[(size_t)*ch]; \
      if (*at == 0) return -1; \
      if (state[*at] == 0) return -1; \
      \
      it = CSSOM_Deque_FSMTableRow_##suffix##_at(table->data, *at); \
    } \
    \
    return (*it)[0]; \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_add( \
    const CSSOM_FSMTable_##suffix *table, int *state, const char *key) \
  { \
    const char *ch; \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    it = CSSOM_Deque_FSMTableRow_##suffix##_begin(table->data); \
    for (ch = key; *ch != '\0'; ++ch) { \
      int *at; \
      \
      at = &(*it)[(size_t)*ch]; \
      if (*at == 0) return -1; \
      ++state[*at]; \
      \
      it = CSSOM_Deque_FSMTableRow_##suffix##_at(table->data, *at); \
    } \
    \
    return (*it)[0]; \
  } \
  \
  \
  \
  static int FSMTable_##suffix##_remove( \
    const CSSOM_FSMTable_##suffix *table, int *state, const char *key) \
  { \
    const char *ch; \
    CSSOM_DequeIter_FSMTableRow_##suffix it; \
    \
    it = CSSOM_Deque_FSMTableRow_##suffix##_begin(table->data); \
    for (ch = key; *ch != '\0'; ++ch) { \
      int *at; \
      \
      at = &(*it)[(size_t)*ch]; \
      if (*at == 0) return -1; \
      --state[*at]; \
      \
      it = CSSOM_Deque_FSMTableRow_##suffix##_at(table->data, *at); \
    } \
    \
    return (*it)[0]; \
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
    int *state; \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
  }; \
  \
  \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc( \
    const CSSOM_FSMTable_##suffix *table) \
  { \
    int *state; \
    CSSOM_Vector_FSMItemPtr_##suffix *refs; \
    CSSOM_Deque_FSMItem_##suffix *data; \
    CSSOM_FSM_##suffix *fsm; \
    CSSOM_VectorIter_FSMItemPtr_##suffix refsit; \
    \
    state = (int*)malloc(sizeof(int) * FSMTable_##suffix##_size(table)); \
    if (state == NULL) return NULL; \
    \
    memset(state, 0, sizeof(int) * FSMTable_##suffix##_size(table)); \
    \
    refs = CSSOM_Vector_FSMItemPtr_##suffix##_alloc( \
      FSMTable_##suffix##_amount(table)); \
    if (refs == NULL) { \
      free(state); \
      return NULL; \
    } \
    \
    data = CSSOM_Deque_FSMItem_##suffix##_alloc_ex(0, \
      FSMTable_##suffix##_amount(table)); \
    if (data == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
      free(state); \
      return NULL; \
    } \
    \
    fsm = (CSSOM_FSM_##suffix*)malloc(sizeof(CSSOM_FSM_##suffix)); \
    if (fsm == NULL) { \
      CSSOM_Vector_FSMItemPtr_##suffix##_free(refs); \
      CSSOM_Deque_FSMItem_##suffix##_free(data); \
      free(state); \
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
    fsm->state = state; \
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
    free(fsm->state); \
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
    hash = FSMTable_##suffix##_find(fsm->table, fsm->state, key); \
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
    hash = FSMTable_##suffix##_add(fsm->table, fsm->state, key); \
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
    hash = FSMTable_##suffix##_remove(fsm->table, fsm->state, position->key); \
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
