#include "test_CSSStyleDeclarationValue.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPropertyValue.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleDeclarationValue.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void getProperty() {
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

  cssom::CSSStyleDeclarationValue values = style.values();

  assert(values.getProperty("color").isNull() == false);
  assert(values.getProperty("background-color").isNull() == false);
  assert(values.getProperty("font-face").isNull() == true);
}



} // unnamed

namespace test {



void cssStyleDeclarationValue() {
  getProperty();
}



} // test
