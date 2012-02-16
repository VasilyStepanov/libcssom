#include "test_CSSStyleSheet.h"

#include "src/CSSStyleSheet.h"
#include "src/CSSRule.h"
#include "src/CSSStyleRule.h"

#include <cssom/types.h>

#include <assert.h>



static void test_CSSStyleSheet_append() {
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule *cssRule1, *cssRule2, *cssRule3;
  const CSSOM_CSSRuleList *cssRules;

  cssRule1 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc();
  cssRule2 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc();
  cssRule3 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc();
  styleSheet = CSSOM_CSSStyleSheet_alloc();



  CSSOM_CSSStyleSheet_append(styleSheet, cssRule1);
  CSSOM_CSSStyleSheet_append(styleSheet, cssRule2);

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(cssRules[0] == cssRule1);
  assert(cssRules[1] == cssRule2);
  assert(cssRules[2] == NULL);
  assert(cssRules == CSSOM_CSSStyleSheet_cssRules(styleSheet));



  CSSOM_CSSStyleSheet_append(styleSheet, cssRule3);
  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(cssRules[0] == cssRule1);
  assert(cssRules[1] == cssRule2);
  assert(cssRules[2] == cssRule3);
  assert(cssRules[3] == NULL);
  assert(cssRules == CSSOM_CSSStyleSheet_cssRules(styleSheet));



  CSSOM_CSSStyleSheet_free(styleSheet);
}



void test_CSSStyleSheet() {
  test_CSSStyleSheet_append();
}
