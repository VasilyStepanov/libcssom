#ifndef _CSSOM_CSSOM_H
#define _CSSOM_CSSOM_H

#include <cssom/CSSOM.h>

#include "FSM_CSSProperty.h"

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_acquire(CSSOM *cssom);

void CSSOM_release(CSSOM *cssom);

CSSOM_CSSRule * CSSOM__parseCSSRule(const CSSOM *cssom,
  CSSOM_CSSStyleSheet *styleSheet, const char * cssText, int len);

void CSSOM__invalidModificationErr(const CSSOM *cssom);

void CSSOM__indexSizeErr(const CSSOM *cssom);

int CSSOM__error(const CSSOM *cssom, const SAC_Error *error);

const CSSOM_FSMTable_CSSProperty* CSSOM__table(const CSSOM *cssom);



#ifdef __cplusplus
}
#endif

#endif
