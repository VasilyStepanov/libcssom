#include "test_Parser.h"

#include <cssom/Parser.h>
#include <cssom/CSSRule.h>
#include <cssom/types.h>

#include <assert.h>



static void test_Parser_basics() {
  CSSOM_Parser *parser;
  CSSOM_CSSStyleSheet *styleSheet;
  const CSSOM_CSSRuleList *cssRules;
  
  parser = CSSOM_Parser_alloc();

  styleSheet = CSSOM_Parser_parseStyleSheet(parser,
"p {\n"
"  color : green\n"
"}\n"
  );

  cssRules = CSSOM_CSSStyleSheet_cssRules(styleSheet);

  assert(CSSOM_CSSRule_type(cssRules[0]) == CSSOM_STYLE_RULE);
  assert(cssRules[1] == NULL);

  CSSOM_CSSStyleSheet_free(styleSheet);

  CSSOM_Parser_free(parser);
}



void test_Parser() {
  test_Parser_basics();
}
