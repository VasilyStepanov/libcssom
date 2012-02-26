#include "test_CSSRule.h"

#include "src/CSSRule.h"
#include "src/CSSStyleRule.h"
#include <cssom/CSSRule.h>
#include <cssom/CSSStyleRule.h>

#include <assert.h>



static void test_CSSRule_alloc() {
  CSSOM_CSSRule *cssRule = (CSSOM_CSSRule*)CSSOM_CSSStyleRule_alloc(NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_STYLE_RULE);

  CSSOM_CSSRule_free(cssRule);
}



void test_CSSRule() {
  test_CSSRule_alloc();
}
