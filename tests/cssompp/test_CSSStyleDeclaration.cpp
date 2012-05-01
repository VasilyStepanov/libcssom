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



void item() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "color";
  assertEquals(cssText, style.item(0));

  cssText = "background-color";
  assertEquals(cssText, style.item(1));

  assert(style.item(2) == NULL);
}



} // unnamed

namespace test {



void cssStyleDeclaration() {
  parentRule();
  item();
}



} // test
