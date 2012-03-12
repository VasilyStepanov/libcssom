#include "test_CSSRule.h"

#include "cssom-src/CSSProperty.h"
#include "cssom-src/CSSRule.h"
#include "cssom-src/CSSStyleRule.h"

#include <assert.h>



static void test_CSSRule_alloc() {
  const char *map[] = {
    NULL
  };

  CSSOM_FSMTable_CSSProperty *table = CSSOM_FSMTable_CSSProperty_alloc(
    map, CSSOM_CSSProperty__release);
  CSSOM_CSSRule *cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule__alloc(
    table, NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_STYLE_RULE);

  CSSOM_CSSRule__release(cssRule);
  CSSOM_FSMTable_CSSProperty_free(table);
}



void test_CSSRule() {
  test_CSSRule_alloc();
}
