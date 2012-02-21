#include "test_List.h"
#include "test_CSSRule.h"
#include "test_CSSStyleSheet.h"
#include "test_parser.h"

#include <stdlib.h>



int main() {
  test_List();
  test_CSSRule();
  test_CSSStyleSheet();
  test_parser();
  return EXIT_SUCCESS;
}
