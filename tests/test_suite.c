#include "test_List.h"
#include "test_CSSRule.h"
#include "test_CSSStyleSheet.h"
#include "test_Parser.h"

#include <stdlib.h>



int main() {
  test_List();
  test_CSSRule();
  test_CSSStyleSheet();
  test_Parser();
  return EXIT_SUCCESS;
}
