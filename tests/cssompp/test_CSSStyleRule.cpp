#include "test_CSSStyleRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void selectorText() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("p"), cssRule.selectorText());
}



} // unnamed

namespace test {



void cssStyleRule() {
  selectorText();
}



} // test
