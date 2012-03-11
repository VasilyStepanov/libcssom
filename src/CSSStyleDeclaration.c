#include "CSSStyleDeclaration.h"

#include "CSSProperty.h"

#include <stdlib.h>

#include "gcc.h"



struct _CSSOM_CSSStyleDeclaration {
  CSSOM_FSM_CSSProperty *fsm;
};



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  const CSSOM_FSMTable_CSSProperty *table)
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_FSM_CSSProperty *fsm;

  fsm = CSSOM_FSM_CSSProperty_alloc(table);
  if (fsm == NULL) return NULL;

  style = (CSSOM_CSSStyleDeclaration*)malloc(sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) {
    CSSOM_FSM_CSSProperty_free(fsm);
    return NULL;
  }

  style->fsm = fsm;

  return style;
}



void CSSOM_CSSStyleDeclaration__free(CSSOM_CSSStyleDeclaration *style) {
  CSSOM_FSMIter_CSSProperty it;

  for (
    it = CSSOM_FSM_CSSProperty_begin(style->fsm);
    it != CSSOM_FSM_CSSProperty_end(style->fsm);
    it = CSSOM_FSMIter_CSSProperty_next(it))
  {
    CSSOM_CSSProperty__free(it->value);
  }

  CSSOM_FSM_CSSProperty_free(style->fsm);
  free(style);
}



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_size(style->fsm);
}



CSSOM_CSSProperty* CSSOM_CSSStyleDeclaration__setProperty(
  CSSOM_CSSStyleDeclaration *style,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSProperty *prop;
  CSSOM_FSMIter_CSSProperty it;

  prop = CSSOM_CSSProperty__alloc(value, important);
  if (prop == NULL) return NULL;

  it = CSSOM_FSM_CSSProperty_add(style->fsm, property, prop);
  if (it == CSSOM_FSM_CSSProperty_end(style->fsm)) {
    CSSOM_CSSProperty__free(prop);
    return NULL;
  }

  CSSOM_CSSProperty__setName(prop, it->key);

  return prop;
}



const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_FSMIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_find(style->fsm, property);
  if (it == CSSOM_FSM_CSSProperty_end(style->fsm)) return NULL;

  return CSSOM_CSSProperty_cssText(it->value);
}
