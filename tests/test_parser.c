#include "test_parser.h"

#include <cssom/parser.h>



static void test_parser_basics() {
  CSSOM_Parser *parser = CSSOM_Parser_create();
  CSSOM_Parser_release(parser);
}



void test_parser() {
  test_parser_basics();
}
