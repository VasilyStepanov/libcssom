#include "test_CSSOM.h"

#include "test_utils.h"

#include <cssom.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>



static void test_CSSOM_basics() {
  const char *css =
"p {\n"
"  color : green\n"
"}\n";

  CSSOM *cssom;
  CSSOM_CSSStyleSheet *styleSheet;
  const CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSRule *cssRule;
  const CSSOM_CSSStyleDeclaration *style;
  
  cssom = CSSOM_create(CSSOM_CSSProperties);
  styleSheet = CSSOM_parse(cssom, css, strlen(css));

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);

  cssRule = CSSOM_CSSRuleList_at(cssRules, 0);
  assert(cssRule != NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_STYLE_RULE);

  ASSERT_EQUAL_STRINGS("p",
    CSSOM_CSSStyleRule_selectorText((CSSOM_CSSStyleRule*)cssRule));

  style = CSSOM_CSSStyleRule_style((CSSOM_CSSStyleRule*)cssRule);

  assert(CSSOM_CSSStyleDeclaration_length(style) == 1);

  ASSERT_EQUAL_STRINGS("green",
    CSSOM_CSSStyleDeclaration_getPropertyValue(style, "color"));
  ASSERT_EQUAL_STRINGS("",
    CSSOM_CSSStyleDeclaration_getPropertyPriority(style, "color"));
  ASSERT_EQUAL_STRINGS("color : green;",
    CSSOM_CSSStyleDeclaration_cssText(style));

  CSSOM_CSSStyleSheet_dispose(styleSheet);
  CSSOM_dispose(cssom);
}



void test_CSSOM() {
  test_CSSOM_basics();
}
