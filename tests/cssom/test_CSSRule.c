#include "test_CSSRule.h"

#include "src/CSSProperty.h"
#include "src/CSSStyleRule.h"

#include <cssom/CSSRule.h>

#include <assert.h>



static void test_CSSRule_alloc(void) {
  const char *map[] = {
    NULL
  };

  CSSOM_FSMTable_CSSProperty *table = CSSOM_FSMTable_CSSProperty_alloc(
    map, CSSOM_CSSProperty_release);
  CSSOM_CSSRule *cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(
    table, NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_CSSRule_STYLE_RULE);

  CSSOM_CSSRule_release(cssRule);
  CSSOM_FSMTable_CSSProperty_free(table);
}



void test_CSSRule(void) {
  test_CSSRule_alloc();
}
