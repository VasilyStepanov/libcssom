#ifndef _CSSOM_CSSSTYLERULE_H
#define _CSSOM_CSSSTYLERULE_H

#include <cssom/CSSStyleRule.h>

#include "FSM_CSSProperty.h"

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  const CSSOM_FSMTable_CSSProperty *table);



#ifdef __cplusplus
}
#endif

#endif
