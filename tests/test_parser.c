#include "test_parser.h"

#include <cssom/parser.h>



static void test_parser_basics() {
  CSSOM_Parser *parser;
  CSSOM_CSSStyleSheet *styleSheet;
  
  parser = CSSOM_Parser_alloc();

  styleSheet = CSSOM_Parser_parseStyleSheet(parser,
"p {\n"
"  color : green\n"
"}\n"
  );

  CSSOM_CSSStyleSheet_free(styleSheet);

  CSSOM_Parser_free(parser);
}



void test_parser() {
  test_parser_basics();
}
