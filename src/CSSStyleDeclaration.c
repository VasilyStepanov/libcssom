#include "CSSStyleDeclaration.h"

#include <stdlib.h>

#include "gcc.h"



struct _CSSOM_CSSStyleDeclaration {
  unsigned long length;
};



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration_alloc() {
  CSSOM_CSSStyleDeclaration *style;

  style = (CSSOM_CSSStyleDeclaration*)malloc(sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) return NULL;

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



void CSSOM_CSSStyleDeclaration_setProperty(CSSOM_CSSStyleDeclaration *style,
  const char *property CSSOM_UNUSED, const char *value CSSOM_UNUSED)
{
  ++style->length;
}