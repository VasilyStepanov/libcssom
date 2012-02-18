#include "test_Parser.h"

#include "test_utils.h"

#include <cssom/Parser.h>
#include <cssom/CSSRule.h>
#include <cssom/CSSStyleRule.h>
#include <cssom/CSSStyleDeclaration.h>

#include <assert.h>
#include <stdlib.h>



static void test_Parser_basics() {
  CSSOM_Parser *parser;
  CSSOM_CSSStyleSheet *styleSheet;
  const CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSRule *cssRule;
  const CSSOM_CSSStyleDeclaration *style;
  
  parser = CSSOM_Parser_alloc();

  styleSheet = CSSOM_Parser_parseStyleSheet(parser,
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

  CSSOM_CSSStyleSheet_free(styleSheet);

  CSSOM_Parser_free(parser);
}



void test_Parser() {
  test_Parser_basics();
}
