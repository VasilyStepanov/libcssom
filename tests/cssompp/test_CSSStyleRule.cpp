#include "test_CSSStyleRule.hpp"

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

  assertEquals(std::string("p"), cssRule.selectorText());



  cssText = "h1, h2, h3 { color : green; }";
  cssRule.setSelectorText("h1, h2, h3");
  assertEquals(std::string("h1, h2, h3"), cssRule.selectorText());
  assertEquals(cssText, cssRule.cssText());


  assert(errors.syntaxErrors == 0);
  cssRule.setSelectorText("& h4");
  assert(errors.syntaxErrors == 1);
  assertEquals(std::string("h1, h2, h3"), cssRule.selectorText());
}



void selector() {
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



void cssStyleRule() {
  selectorText();
  selector();
}



} // test
