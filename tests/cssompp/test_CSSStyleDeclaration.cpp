#include "test_CSSStyleDeclaration.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void parentRule() {
  std::string cssText;
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();


  assert(style.parentRule() == cssRule);
}



} // unnamed

namespace test {



void cssStyleDeclaration() {
  parentRule();
}



} // test
