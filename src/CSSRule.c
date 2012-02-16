#include "CSSRule.h"
#include <cssom/CSSRule.h>
#include <cssom/CSSStyleRule.h>
#include <cssom/CSSStyleDeclaration.h>

#include <stdlib.h>

#include <stdio.h>



struct _CSSOM_CSSRule_vtable {
  void (*free)(CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSRule {
  struct _CSSOM_CSSRule_vtable *vtable;
  CSSOM_CSSRuleType type;
};



struct _CSSOM_CSSStyleRule {
  CSSOM_CSSRule super;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSStyleRule_free(CSSOM_CSSStyleRule *cssRule) {
  free(cssRule);
}

static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_free
};



static void CSSOM_CSSRule_init(CSSOM_CSSRule *cssRule, CSSOM_CSSRuleType type) {
  cssRule->type = type;
}



void CSSOM_CSSRule_free(CSSOM_CSSRule *cssRule) {
  cssRule->vtable->free(cssRule);
}



CSSOM_CSSRuleType CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule) {
  return cssRule->type;
}



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule_alloc() {
  CSSOM_CSSStyleRule *cssRule;

  cssRule = (CSSOM_CSSStyleRule*)malloc(sizeof(CSSOM_CSSStyleRule));
  if (cssRule == NULL) return NULL;

  CSSOM_CSSRule_init((CSSOM_CSSRule*)cssRule, CSSOM_STYLE_RULE);
  ((CSSOM_CSSRule*)cssRule)->vtable = &CSSStyleRule_vtable;

  return cssRule;
}



const CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(
  CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->style;
}
