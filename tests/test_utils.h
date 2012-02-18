#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string.h>
#include <stdio.h>
#include <math.h>



#define ASSERT_EQUAL_STRINGS(lhs, rhs) \
  do { \
    int eq; \
    const char *lhsval = (lhs); \
    const char *rhsval = (rhs); \
    assert(lhsval != NULL); \
    assert(rhsval != NULL); \
    eq = strcmp(lhsval, rhsval); \
    if (eq != 0) { \
      printf( \
"Expected: %s\n" \
"Received: %s\n", \
      lhsval, rhsval); \
    } \
    assert(eq == 0); \
  } while (0)



#define ASSERT_EQUAL_REALS(lhs, rhs) \
  assert(fabs(lhs - rhs) < 1e-7)


#endif
