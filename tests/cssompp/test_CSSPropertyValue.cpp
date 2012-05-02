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



void cssText() {
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
  cssom::CSSStyleDeclarationValue values = style.values();
  cssom::CSSPropertyValue color = values.getProperty("color");
  cssom::CSSPropertyValue backgroundColor = values.getProperty(
    "background-color");

  cssText = "green";
  assertEquals(cssText, color.cssText());

  cssText = "maroon";
  assertEquals(cssText, backgroundColor.cssText());
}



} // unnamed

namespace test {



void cssPropertyValue() {
  cssText();
}



} // test
