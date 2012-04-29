#ifndef TEST_ERRORS_HPP
#define TEST_ERRORS_HPP

#include <cssompp/CSSOM.hpp>

#include <stddef.h>

namespace test {



struct Errors {
  size_t syntaxErrors;
  size_t invalidModificationErrors;
  size_t indexSizeErrors;
  size_t hierarchyRequestErrors;

  Errors() :
    syntaxErrors(0),
    invalidModificationErrors(0),
    indexSizeErrors(0),
    hierarchyRequestErrors(0)
  {}
};



int errorHandler(void *userData, const CSSOM_Error *error);



} // test

#endif // TEST_ERRORS_HPP
