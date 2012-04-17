#include "test_CSSStyleSheet.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/CSSStyleRule.hpp>

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



void insertRule() {
  Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
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


  /**
   * TODO: Add HIERARCHY_REQUEST_ERR test.
   */
}



void deleteRule() {
  Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(errorHandler);
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
