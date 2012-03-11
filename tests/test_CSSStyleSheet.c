#include "test_CSSStyleSheet.h"

#include "src/CSSProperty.h"
#include "src/CSSRule.h"
#include "src/CSSStyleRule.h"
#include "src/CSSStyleSheet.h"

#include <stdlib.h>
#include <assert.h>



static void test_CSSStyleSheet_append() {
  const char *map[] = {
    NULL
  };

  CSSOM_FSMTable_CSSProperty *table;
  CSSOM_CSSStyleSheet *styleSheet;
  CSSOM_CSSRule *cssRule1, *cssRule2, *cssRule3;
  const CSSOM_CSSRuleList *cssRules;

  table = CSSOM_FSMTable_CSSProperty_alloc(map, CSSOM_CSSProperty__release);
  cssRule1 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(table);
  cssRule2 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(table);
  cssRule3 = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(table);
  styleSheet = CSSOM_CSSStyleSheet__alloc(NULL);



  CSSOM_CSSStyleSheet__append(styleSheet, cssRule1);
  CSSOM_CSSStyleSheet__append(styleSheet, cssRule2);

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(cssRules[0] == cssRule1);
  assert(cssRules[1] == cssRule2);
  assert(cssRules[2] == NULL);
  assert(cssRules == CSSOM_CSSStyleSheet_cssRules(styleSheet));



  CSSOM_CSSStyleSheet__append(styleSheet, cssRule3);
  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(cssRules[0] == cssRule1);
  assert(cssRules[1] == cssRule2);
  assert(cssRules[2] == cssRule3);
  assert(cssRules[3] == NULL);
  assert(cssRules == CSSOM_CSSStyleSheet_cssRules(styleSheet));



  CSSOM_CSSStyleSheet_dispose(styleSheet);
  CSSOM_FSMTable_CSSProperty_free(table);
}



void test_CSSStyleSheet() {
  test_CSSStyleSheet_append();
}
