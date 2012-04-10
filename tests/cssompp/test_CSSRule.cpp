#include "test_CSSRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



struct Errors {
  size_t invalidModificationErrors;

  Errors() :
    invalidModificationErrors(0)
  {}
};



void consts() {
  assert(cssom::CSSRule::STYLE_RULE == 1);
  assert(cssom::CSSRule::IMPORT_RULE == 3);
  assert(cssom::CSSRule::MEDIA_RULE == 4);
  assert(cssom::CSSRule::FONT_FACE_RULE == 5);
  assert(cssom::CSSRule::PAGE_RULE == 6);
  assert(cssom::CSSRule::NAMESPACE_RULE == 10);
}



void type() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule style = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);

  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
}



int errorHandler(void *userData, const CSSOM_Error *error) {
  Errors *errors = static_cast<Errors*>(userData);

  switch (error->code) {
    case CSSOM_ERROR_NOT_SUPPORTED:
      break;
    case CSSOM_ERROR_SYNTAX:
      break;
    case CSSOM_ERROR_INVALID_MODIFICATION_ERR:
      ++errors->invalidModificationErrors;
      break;
  }

  return 0;
}



void cssText() {
  Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule style = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  std::string cssText;



  /**
   * cssText()
   */

  cssText = "p { color : green; }";
  assertEquals(cssText, style.cssText());



  /**
   * setCSSText()
   */

  style.setCSSText(
"div {\n"
" background-color : green;\n"
"}\n"
  );
  cssText = "div { background-color : green; }";
  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
  assertEquals(cssText, style.cssText());



  style.setCSSText("invalid");
  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
  assertEquals(cssText, style.cssText());



  assert(errors.invalidModificationErrors == 0);
  style.setCSSText("@page {}");
  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
  assertEquals(cssText, style.cssText());
  assert(errors.invalidModificationErrors == 1);
}



void selectorText() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule style = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("p"), style.selectorText());
}



void parentStyleSheet() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule style = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);

  assert(style.parentStyleSheet() == styleSheet);


  /**
   * Test on swap.
   */

  style.setCSSText(
"div {\n"
" background-color : green;\n"
"}\n"
  );

  assert(style.parentStyleSheet() == styleSheet);
}



} // unnamed

namespace test {



void cssRule() {
  consts();
  type();
  cssText();
  parentStyleSheet();
}



} // test