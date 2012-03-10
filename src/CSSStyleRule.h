#ifndef _CSSOM_CSSSTYLERULE_H
#define _CSSOM_CSSSTYLERULE_H

#include <cssom/CSSStyleRule.h>

#include "FSM_CSSProperty.h"



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule_alloc(
  const CSSOM_FSMTable_CSSProperty *table);



#endif
