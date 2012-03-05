#ifndef CSSOM_FSM_H
#define CSSOM_FSM_H

#include <stddef.h>



typedef struct _CSSOM_FSM CSSOM_FSM;




CSSOM_FSM* CSSOM_FSM_alloc(const char **map);

void CSSOM_FSM_free(CSSOM_FSM *fsm);

int CSSOM_FSM_find(const CSSOM_FSM *fsm, const char *key);

size_t CSSOM_FSM_size(const CSSOM_FSM *fsm);



#endif
