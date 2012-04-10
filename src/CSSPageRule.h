#ifndef _CSSOM_CSS_PAGE_RULE_H
#define _CSSOM_CSS_PAGE_RULE_H

#include <cssom/CSSPageRule.h>

#include "FSM_CSSProperty.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSPageRule* CSSOM_CSSPageRule__alloc(
  CSSOM_CSSStyleSheet *parentStyleSheet,
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[]);



#ifdef __cplusplus
}
#endif

#endif