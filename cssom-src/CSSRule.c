#include "CSSRule.h"
#include "CSSStyleRule.h"

#include "CSSStyleDeclaration.h"
#include "CSSEmitter.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



struct _CSSOM_CSSRule_vtable {
  void (*release)(CSSOM_CSSRule *cssRule);
};



struct _CSSOM_CSSRule {
  struct _CSSOM_CSSRule_vtable *vtable;
  size_t handles;
  CSSOM_CSSRuleType type;
};



struct _CSSOM_CSSStyleRule {
  CSSOM_CSSRule super;
  char *selectorText;
  const SAC_Selector **selectors;
  CSSOM_CSSStyleDeclaration *style;
};



static void CSSStyleRule_release(CSSOM_CSSStyleRule *cssRule) {
  assert(((CSSOM_CSSRule*)cssRule)->handles > 0);
  --((CSSOM_CSSRule*)cssRule)->handles;
  if (((CSSOM_CSSRule*)cssRule)->handles > 0) return;

  CSSOM_CSSStyleDeclaration__release(cssRule->style);
  free(cssRule->selectorText);
  free(cssRule);
}

static struct _CSSOM_CSSRule_vtable CSSStyleRule_vtable = {
  (void(*)(CSSOM_CSSRule*))&CSSStyleRule_release
};



static void CSSRule_init(CSSOM_CSSRule *cssRule,
  struct _CSSOM_CSSRule_vtable *vtable, CSSOM_CSSRuleType type)
{
  cssRule->vtable = vtable;
  cssRule->handles = 1;
  cssRule->type = type;
}



void CSSOM_CSSRule__acquire(CSSOM_CSSRule *cssRule) {
  ++cssRule->handles;
}



void CSSOM_CSSRule__release(CSSOM_CSSRule *cssRule) {
  cssRule->vtable->release(cssRule);
}



CSSOM_CSSRuleType CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule) {
  return cssRule->type;
}



CSSOM_CSSStyleRule* CSSOM_CSSStyleRule__alloc(
  const CSSOM_FSMTable_CSSProperty *table, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_CSSStyleRule *cssRule;

  style = CSSOM_CSSStyleDeclaration__alloc(table);
  if (style == NULL) return NULL;

  cssRule = (CSSOM_CSSStyleRule*)malloc(sizeof(CSSOM_CSSStyleRule));
  if (cssRule == NULL) {
    CSSOM_CSSStyleDeclaration__release(style);
    return NULL;
  }

  CSSRule_init((CSSOM_CSSRule*)cssRule, &CSSStyleRule_vtable, CSSOM_STYLE_RULE);
  cssRule->selectorText = NULL;
  cssRule->selectors = selectors;
  cssRule->style = style;

  return cssRule;
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleRule_style(
  const CSSOM_CSSStyleRule *cssRule)
{
  return cssRule->style;
}



const char* CSSOM_CSSStyleRule_selectorText(
  const CSSOM_CSSStyleRule *cssRule)
{
  if (cssRule->selectorText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_selectors(out, cssRule->selectors) != 0) {
      fclose(out);
      free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleRule*)cssRule)->selectorText = buf;
  }
  return cssRule->selectorText;
}
