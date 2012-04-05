#ifndef _CSSOM_CSSSTYLERULE_H
#define _CSSOM_CSSSTYLERULE_H

#include <cssom/CSSStyleRule.h>

#include "FSM_CSSProperty.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet,
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[]);



const SAC_Selector** CSSOM_CSSStyleRule__selectors(
  const CSSOM_CSSStyleRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
