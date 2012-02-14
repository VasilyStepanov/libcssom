#include "test_CSSRule.h"

#include "src/CSSRule.h"
#include <cssom/CSSRule.h>

#include <assert.h>



static void test_CSSRule_alloc() {
  CSSOM_CSSRule *rule = CSSOM_CSSRule_alloc(CSSOM_STYLE_RULE);

  assert(CSSOM_CSSRule_type(rule) == CSSOM_STYLE_RULE);

  CSSOM_CSSRule_free(rule);
}



void test_CSSRule() {
  test_CSSRule_alloc();
}
