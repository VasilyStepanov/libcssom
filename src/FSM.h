#ifndef CSSOM_FSM_H
#define CSSOM_FSM_H



typedef struct _CSSOM_FSM CSSOM_FSM;

typedef struct _CSSOM_FSMItem CSSOM_FSMItem;



struct _CSSOM_FSMItem {
  const char *key;
  int value;
};



CSSOM_FSM* CSSOM_FSM_alloc(const CSSOM_FSMItem *map);

void CSSOM_FSM_free(CSSOM_FSM *fsm);

int CSSOM_FSM_find(const CSSOM_FSM *fsm, const char *key);



#endif
