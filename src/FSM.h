#ifndef CSSOM_FSM_H
#define CSSOM_FSM_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_FSM_DECLARE(T, suffix) \
  typedef struct _CSSOM_FSMItem_##suffix { \
    const char *key; \
    int hash; \
    T value; \
  } CSSOM_FSMItem_##suffix; \
  \
  \
  \
  typedef struct _CSSOM_FSMTable_##suffix CSSOM_FSMTable_##suffix; \
  \
  CSSOM_FSMTable_##suffix* CSSOM_FSMTable_##suffix##_alloc(const char **map); \
  void CSSOM_FSMTable_##suffix##_free(CSSOM_FSMTable_##suffix *table); \
  \
  typedef struct _CSSOM_FSM_##suffix CSSOM_FSM_##suffix; \
  typedef CSSOM_FSMItem_##suffix* CSSOM_FSMIter_##suffix; \
  typedef const CSSOM_FSMItem_##suffix* CSSOM_FSMConstIter_##suffix; \
  \
  CSSOM_FSM_##suffix* CSSOM_FSM_##suffix##_alloc( \
    const CSSOM_FSMTable_##suffix *table); \
  void CSSOM_FSM_##suffix##_free(CSSOM_FSM_##suffix *fsm); \
  size_t CSSOM_FSM_##suffix##_size(const CSSOM_FSM_##suffix *fsm); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_insert( \
    CSSOM_FSM_##suffix *fsm, const char *key, T value); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_erase( \
    CSSOM_FSM_##suffix *fsm, CSSOM_FSMIter_##suffix position); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_ffind( \
    CSSOM_FSM_##suffix *fsm, int hash); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_find( \
    CSSOM_FSM_##suffix *fsm, const char *key); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_at( \
    CSSOM_FSM_##suffix *fsm, size_t index); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_begin(CSSOM_FSM_##suffix *fsm); \
  CSSOM_FSMIter_##suffix CSSOM_FSM_##suffix##_end(CSSOM_FSM_##suffix *fsm); \
  CSSOM_FSMConstIter_##suffix CSSOM_FSM_##suffix##_cbegin( \
    const CSSOM_FSM_##suffix *fsm); \
  CSSOM_FSMConstIter_##suffix CSSOM_FSM_##suffix##_cend( \
    const CSSOM_FSM_##suffix *fsm); \
  \
  CSSOM_FSMIter_##suffix CSSOM_FSMIter_##suffix##_next( \
    CSSOM_FSMIter_##suffix iter); \
  CSSOM_FSMConstIter_##suffix CSSOM_FSMConstIter_##suffix##_next( \
    CSSOM_FSMConstIter_##suffix iter);



#ifdef __cplusplus
}
#endif

#endif
