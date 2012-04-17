#include "test_CSSMediaRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



struct Errors {
  size_t indexSizeErrors;

  Errors() :
    indexSizeErrors(0)
  {}
};



int errorHandler(void *userData, const CSSOM_Error *error) {
  Errors *errors = static_cast<Errors*>(userData);

  switch (error->code) {
    case CSSOM_ERROR_NOT_SUPPORTED:
      break;
    case CSSOM_ERROR_SYNTAX:
      break;
    case CSSOM_ERROR_INDEX_SIZE_ERR:
      ++errors->indexSizeErrors;
      break;
    case CSSOM_ERROR_INVALID_MODIFICATION_ERR:
      break;
  }

  return 0;
}



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

  // TODO:
  // cssText = "@media screen { p { color : green; } }";
  cssText = "@media { p { color : green; } }";
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
  // cssText = "@media all { p { color : green; } div { color : green; } }";
  cssText = "@media { p { color : green; } div { color : green; } }";
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
  Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
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

  // cssText = "@media { "
  //   "span { color : green; } "
  //   "p { color : green; } "
  // "}";
  cssText = "@media { "
    "span { color : green; } "
    "p { color : green; } "
  "}";
  assertEquals(cssText, cssRule.cssText());



  cssRule.insertRule("div { color : green; }", 2);

  // cssText = "@media { "
  //   "span { color : green; } "
  //   "p { color : green; } "
  //   "div { color : green; } "
  // "}";
  cssText = "@media { "
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


  /**
   * TODO: Add HIERARCHY_REQUEST_ERR test.
   */
}



void deleteRule() {
  Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
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

  cssText = "@media { "
    "span { color : green; } "
    "p { color : green; } "
  "}";
  assertEquals(cssText, cssRule.cssText());



  cssRule.deleteRule(0);

  cssText = "@media { "
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

  cssText = "@media {  }";
  assertEquals(cssText, cssRule.cssText());
}



} // unnamed

namespace test {



void cssMediaRule() {
  cssText();
  cssRules();
  insertRule();
  deleteRule();
}



} // test
