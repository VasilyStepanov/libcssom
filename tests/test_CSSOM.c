#include "test_CSSOM.h"

#include "test_utils.h"

#include <cssom.h>

#include <assert.h>
#include <stdlib.h>



static void test_CSSOM_basics() {
  CSSOM *cssom;
  CSSOM_CSSStyleSheet *styleSheet;
  const CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSRule *cssRule;
  const CSSOM_CSSStyleDeclaration *style;
  
  cssom = CSSOM_create(CSSOM_CSSProperties);
  styleSheet = CSSOM_parse(cssom,
"p {\n"
"  color : green\n"
"}\n"
  );

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);

  assert(cssRules[0] != NULL);
  assert(cssRules[1] == NULL);
  cssRule = cssRules[0];

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_STYLE_RULE);

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
