#include "test_Vector.h"
#include "test_List.h"
#include "test_Deque.h"
#include "test_FSM.h"
#include "test_CSSRule.h"
#include "test_CSSStyleSheet.h"
#include "test_parser.h"

#include <stdlib.h>



int main() {
  test_Vector();
  test_List();
  test_Deque();
  test_FSM();
  test_CSSRule();
  test_CSSStyleSheet();
  test_parser();
  return EXIT_SUCCESS;
}
