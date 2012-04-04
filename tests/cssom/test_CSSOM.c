#include "test_CSSOM.h"

#include "test_utils.h"

#include <cssom.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>



static void test_CSSOM_basics(void) {
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
  styleSheet = CSSOM_parseCSSStyleSheet(cssom, css, strlen(css));

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(CSSOM_CSSRuleList_size(cssRules) == 1);

  cssRule = CSSOM_CSSRuleList_at(cssRules, 0);
  assert(cssRule != NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_CSSRule_STYLE_RULE);

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

  CSSOM_CSSStyleSheet_release(styleSheet);
  CSSOM_release(cssom);
}



static void errorHandler(void *userData, const CSSOM_Error * error) {
  size_t *errors = (size_t*)userData;

  if (error->code == CSSOM_ERROR_SYNTAX) ++(*errors);
}



static void test_CSSOM_errors(void) {
  const char * css =
"p { color:green }\n"
"p { color:green; color } /* malformed declaration missing ':', value */\n"
"p { color:red; color; color:green } /* same with expected recovery */\n"
"p { color:green; color: } /* malformed declaration missing value */\n"
"p { color:red; color:; color:green } /* same with expected recovery */\n"
"p { color:green; color{;color:maroon} } /* unexpected tokens { } */\n"
"p { color:red; color{;color:maroon}; color:green } /* same with recovery */\n";

  CSSOM *cssom;
  CSSOM_CSSStyleSheet *styleSheet;
  const CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSRule *cssRule;
  const CSSOM_CSSStyleDeclaration *style;
  size_t errors = 0;

  cssom = CSSOM_create(CSSOM_CSSProperties);
  CSSOM_setUserData(cssom, &errors);
  CSSOM_setErrorHandler(cssom, errorHandler);

  styleSheet = CSSOM_parseCSSStyleSheet(cssom, css, strlen(css));

  assert(errors == 6);

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);
  assert(CSSOM_CSSRuleList_size(cssRules) == 7);

  cssRule = CSSOM_CSSRuleList_at(cssRules, 6);
  assert(cssRule != NULL);

  assert(CSSOM_CSSRule_type(cssRule) == CSSOM_CSSRule_STYLE_RULE);

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

  CSSOM_CSSStyleSheet_release(styleSheet);
  CSSOM_release(cssom);
}



void test_CSSOM(void) {
  test_CSSOM_basics();
  test_CSSOM_errors();
}
