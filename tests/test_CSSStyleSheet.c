#include "test_CSSStyleSheet.h"

#include "src/CSSStyleSheet.h"
#include "src/CSSRule.h"

#include <cssom/types.h>

#include <assert.h>



static void test_CSSStyleSheet_append() {
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule *cssRule1, *cssRule2, *cssRule3;
  const CSSOM_CSSRuleList *cssRules;

  cssRule1 = CSSOM_CSSRule_alloc(CSSOM_STYLE_RULE);
  cssRule2 = CSSOM_CSSRule_alloc(CSSOM_STYLE_RULE);
  cssRule3 = CSSOM_CSSRule_alloc(CSSOM_STYLE_RULE);
  styleSheet = CSSOM_CSSStyleSheet_alloc();

  CSSOM_CSSStyleSheet_append(styleSheet, cssRule1);
  CSSOM_CSSStyleSheet_append(styleSheet, cssRule2);
  CSSOM_CSSStyleSheet_append(styleSheet, cssRule3);
  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);

  assert(cssRules[0] == cssRule1);
  assert(cssRules[1] == cssRule2);
  assert(cssRules[2] == cssRule3);
  assert(cssRules[3] == NULL);

  CSSOM_CSSStyleSheet_free(styleSheet);
}



void test_CSSStyleSheet() {
  test_CSSStyleSheet_append();
}
