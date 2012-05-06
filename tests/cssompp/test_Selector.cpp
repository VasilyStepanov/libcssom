#include "test_Selector.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/Selector.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void selectorText() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::Selector selector = cssRule.selector();



  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());
}



} // unnamed

namespace test {



void selector() {
  selectorText();
}



} // test
