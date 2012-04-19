#include "test_CSSPageRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void cssText() {
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(&test::errorHandler);
  std::string cssText;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@page {\n"
" color : green\n"
"}\n"
  );

  assert(styleSheet.cssRules().size() == 1);
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::PAGE_RULE);

  cssom::CSSPageRule cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);



  /**
   * cssText()
   */

  cssText = "@page { color : green; }";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@page CompanyLetterHead:first {\n"
" color : green\n"
"}\n"
  );
  cssText = "@page CompanyLetterHead:first { color : green; }";
  assert(cssRule.type() == cssom::CSSRule::PAGE_RULE);
  assertEquals(cssText, cssRule.cssText());



  assert(errors.invalidModificationErrors == 0);
  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(errors.invalidModificationErrors == 1);
  assert(cssRule.type() == cssom::CSSRule::PAGE_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void selectorText() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet;
  cssom::CSSPageRule cssRule;

  /**
   * @page
   */

  styleSheet = cssom.parse(
"@page {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assert(cssRule.type() == cssom::CSSRule::PAGE_RULE);
  assertEquals(std::string(""), cssRule.selectorText());



  /**
   * @page :left
   */

  styleSheet = cssom.parse(
"@page :left {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string(":left"), cssRule.selectorText());



  /**
   * @page LandscapeTable
   */

  styleSheet = cssom.parse(
"@page LandscapeTable {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("LandscapeTable"), cssRule.selectorText());



  /**
   * @page CompanyLetterHead:first
   */

  styleSheet = cssom.parse(
"@page CompanyLetterHead:first {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("CompanyLetterHead:first"), cssRule.selectorText());
}



} // unnamed

namespace test {



void cssPageRule() {
  cssText();
  selectorText();
}



} // test
