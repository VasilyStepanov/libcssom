#include "test_CSSStyleSheet.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/CSSStyleRule.hpp>

#include <assert.h>

namespace {



void insertRule() {
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
"  color : green;\n"
"}\n"
  );

  assert(styleSheet.cssRules().size() == 1);

  styleSheet.insertRule("span { color : green; }", 0);

  assert(styleSheet.cssRules().size() == 2);
  assertEquals(std::string("span"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[0]).selectorText());
  assertEquals(std::string("p"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[1]).selectorText());



  styleSheet.insertRule("div { color : green; }", 2);

  assert(styleSheet.cssRules().size() == 3);
  assertEquals(std::string("span"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[0]).selectorText());
  assertEquals(std::string("p"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[1]).selectorText());
  assertEquals(std::string("div"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[2]).selectorText());



  assert(errors.indexSizeErrors == 0);
  styleSheet.insertRule("p { color : red; }", 4);
  assert(styleSheet.cssRules().size() == 3);
  assert(errors.indexSizeErrors == 1);
  styleSheet.insertRule("p { color : red; }", -1);
  assert(styleSheet.cssRules().size() == 3);
  assert(errors.indexSizeErrors == 2);



  assert(errors.hierarchyRequestErrors == 0);
  styleSheet.insertRule("@import url('foo'); }", 1);
  assert(errors.hierarchyRequestErrors == 1);
  assert(styleSheet.cssRules().size() == 3);
}



void deleteRule() {
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"span {\n"
"  color : green;\n"
"}\n"
"p {\n"
"  color : green;\n"
"}\n"
"div {\n"
"  color : green;\n"
"}\n"
  );

  assert(styleSheet.cssRules().size() == 3);

  styleSheet.deleteRule(2);

  assert(styleSheet.cssRules().size() == 2);
  assertEquals(std::string("span"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[0]).selectorText());
  assertEquals(std::string("p"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[1]).selectorText());



  styleSheet.deleteRule(0);

  assert(styleSheet.cssRules().size() == 1);
  assertEquals(std::string("p"),
    cssom::CSSStyleRule::cast(styleSheet.cssRules()[0]).selectorText());



  assert(errors.indexSizeErrors == 0);

  styleSheet.deleteRule(1);
  assert(styleSheet.cssRules().size() == 1);
  assert(errors.indexSizeErrors == 1);

  styleSheet.deleteRule(-1);
  assert(styleSheet.cssRules().size() == 1);
  assert(errors.indexSizeErrors == 2);



  styleSheet.deleteRule(0);

  assert(styleSheet.cssRules().size() == 0);
}



} // unnamed

namespace test {



void cssStyleSheet() {
  insertRule();
  deleteRule();
}



} // test
