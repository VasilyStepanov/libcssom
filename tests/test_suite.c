#include "test_Vector.h"
#include "test_List.h"
#include "test_Deque.h"
#include "test_FSM.h"
#include "test_CSSRule.h"
#include "test_CSSOM.h"

#include <stdlib.h>



int main() {
  test_Vector();
  test_List();
  test_Deque();
  test_FSM();
  test_CSSRule();
  test_CSSOM();
  return EXIT_SUCCESS;
}
