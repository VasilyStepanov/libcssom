#include "test_CSSMediaRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/MediaList.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void cssText() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::MEDIA_RULE);
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  /**
   * cssText()
   */

  cssText = "@media screen { p { color : green; } }";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@media all {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"  div {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssText = "@media all { p { color : green; } div { color : green; } }";
  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);
  assertEquals(cssText, cssRule.cssText());



  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void cssRules() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  assert(cssRule.cssRules().size() == 1);
  assert(cssRule.cssRules()[0].type() == cssom::CSSRule::STYLE_RULE);
}



void insertRule() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  cssRule.insertRule("span { color : green; }", 0);

  cssText =
"@media screen { "
  "span { color : green; } "
  "p { color : green; } "
"}";
  assertEquals(cssText, cssRule.cssText());



  cssRule.insertRule("div { color : green; }", 2);

  cssText =
"@media screen { "
  "span { color : green; } "
  "p { color : green; } "
  "div { color : green; } "
"}";
  assertEquals(cssText, cssRule.cssText());



  assert(errors.indexSizeErrors == 0);
  cssRule.insertRule("p { color : red; }", 4);
  assertEquals(cssText, cssRule.cssText());
  assert(errors.indexSizeErrors == 1);
  cssRule.insertRule("p { color : red; }", -1);
  assertEquals(cssText, cssRule.cssText());
  assert(errors.indexSizeErrors == 2);



  assert(errors.hierarchyRequestErrors == 0);
  styleSheet.insertRule("@import url('foo'); }", 1);
  assert(errors.hierarchyRequestErrors == 1);
  assert(cssRule.cssRules().size() == 3);
}



void deleteRule() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  span {\n"
"    color : green;\n"
"  }\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"  div {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  cssRule.deleteRule(2);

  cssText =
"@media screen { "
  "span { color : green; } "
  "p { color : green; } "
"}";
  assertEquals(cssText, cssRule.cssText());



  cssRule.deleteRule(0);

  cssText =
"@media screen { "
  "p { color : green; } "
"}";
  assertEquals(cssText, cssRule.cssText());



  assert(errors.indexSizeErrors == 0);

  cssRule.deleteRule(1);
  assertEquals(cssText, cssRule.cssText());
  assert(errors.indexSizeErrors == 1);

  cssRule.deleteRule(-1);
  assertEquals(cssText, cssRule.cssText());
  assert(errors.indexSizeErrors == 2);



  cssRule.deleteRule(0);

  cssText = "@media screen {  }";
  assertEquals(cssText, cssRule.cssText());
}



void media(void) {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  assert(cssRule.media().length() == 1);



  cssRule.setMedia("all, projection");
  assert(cssRule.media().length() == 2);
}



} // unnamed

namespace test {



void cssMediaRule() {
  cssText();
  cssRules();
  insertRule();
  deleteRule();
  media();
}



} // test
