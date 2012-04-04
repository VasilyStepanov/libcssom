#include "test_CSSStyleRule.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>

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



cssom::CSSStyleRule styleRule(const cssom::CSSOM &cssom) {
  cssom::CSSRule cssRule = cssom.parseCSSRule(
"p {\n"
" color : green;\n"
"}\n"
  );
  return cssom::CSSStyleRule(static_cast<cssom::CSSStyleRule&>(cssRule));
}



void consts() {
  assert(cssom::CSSStyleRule::STYLE_RULE == 1);
  assert(cssom::CSSStyleRule::IMPORT_RULE == 3);
  assert(cssom::CSSStyleRule::MEDIA_RULE == 4);
  assert(cssom::CSSStyleRule::FONT_FACE_RULE == 5);
  assert(cssom::CSSStyleRule::PAGE_RULE == 6);
  assert(cssom::CSSStyleRule::NAMESPACE_RULE == 10);
}



void type() {
  cssom::CSSOM cssom;
  cssom::CSSStyleRule style = styleRule(cssom);

  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
}



void errorHandler(void *userData, const CSSOM_Error *error) {
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
}



void cssText() {
  Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
  cssom::CSSStyleRule style = styleRule(cssom);
  std::string cssText;



  /**
   * cssText()
   */

  cssText = "p { color : green; }";
  assert(style.cssText() == cssText);



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
  assert(style.cssText() == cssText);



  style.setCSSText("invalid");
  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
  assert(style.cssText() == cssText);



  assert(errors.invalidModificationErrors == 0);
  style.setCSSText("@page ident;");
  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
  assert(style.cssText() == cssText);
  // assert(errors.invalidModificationErrors == 1);
}



void selectorText() {
  cssom::CSSOM cssom;
  cssom::CSSStyleRule style = styleRule(cssom);

  assert(style.selectorText() == std::string("p"));
}



} // unnamed

namespace test {



void cssStyleRule() {
  consts();
  type();
  selectorText();
  cssText();
}



} // test
