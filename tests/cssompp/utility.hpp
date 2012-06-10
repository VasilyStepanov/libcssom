#ifndef TEST_UTILITY_HPP
#define TEST_UTILITY_HPP

#include <iostream>

#include <assert.h>



#define assertEquals(lhs, rhs) \
  do { \
    std::string lhsval = (lhs); \
    const char *rhsval = (rhs); \
    \
    if (rhsval == NULL) { \
      std::cerr << "'" << lhsval << "' != NULL" << std::endl; \
      assert(rhsval != NULL); \
    } else { \
      bool match = lhsval == rhsval; \
      if (!match) { \
        std::cerr << "'" << lhsval << "'" << " != " \
          << "'" << rhsval << "'" << std::endl; \
        assert(lhsval == rhsval); \
      } \
    } \
  } while (0)



#endif // TEST_UTILITY
