#include "CSSStyleDeclaration.h"

#include <stdlib.h>

#include "gcc.h"



struct _CSSOM_CSSStyleDeclaration {
  const CSSOM_FSM *fsm;
  unsigned long length;
};



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration_alloc(
  const CSSOM_FSM *fsm)
{
  CSSOM_CSSStyleDeclaration *style;

  style = (CSSOM_CSSStyleDeclaration*)malloc(sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) return NULL;

  style->fsm = fsm;
  style->length = 0;

  return style;
}



void CSSOM_CSSStyleDeclaration_free(CSSOM_CSSStyleDeclaration *style) {
  free(style);
}



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style)
{
  return style->length;
}



void CSSOM_CSSStyleDeclaration_append(CSSOM_CSSStyleDeclaration *style,
  const char *property CSSOM_UNUSED,
  const SAC_LexicalUnit *value CSSOM_UNUSED,
  SAC_Boolean important CSSOM_UNUSED)
{
  ++style->length;
}



const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style CSSOM_UNUSED,
  const char *property CSSOM_UNUSED)
{
  return "green";
}
