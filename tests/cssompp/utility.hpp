#ifndef TEST_UTILITY_HPP
#define TEST_UTILITY_HPP

#include <iostream>

#include <assert.h>



#define assertEquals(lhs, rhs) \
  do { \
    bool match = (lhs) == (rhs); \
    if (!match) { \
      std::cerr << "'" << (lhs) << "'" << " != " \
        << "'" << (rhs) << "'" << std::endl; \
      assert((lhs) == (rhs)); \
    } \
  } while (0)



#endif // TEST_UTILITY
