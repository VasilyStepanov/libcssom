#ifndef _CSSOM_SELECTOR_H
#define _CSSOM_SELECTOR_H

#include <cssom/typedefs.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_Selector CSSOM_Selector;

CSSOM_Selector* CSSOM_Selector__alloc(CSSOM_CSSRule *ownerRule,
  const SAC_Selector *selectors[]);

void CSSOM_Selector_acquire(CSSOM_Selector *selector);

void CSSOM_Selector_release(CSSOM_Selector *selector);

CSSOM_CSSRule* CSSOM_Selector__ownerRule(const CSSOM_Selector *selector);

const char* CSSOM_Selector_selectorText(const CSSOM_Selector *selector);

const SAC_Selector** CSSOM_Selector_selectors(const CSSOM_Selector *selector);

void CSSOM_Selector__keepParser(CSSOM_Selector *selector,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif
