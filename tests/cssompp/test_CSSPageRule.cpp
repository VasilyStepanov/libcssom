#include "test_CSSPageRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/Selector.hpp>

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

  assert(styleSheet.cssRules().length() == 1);
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
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
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



  /**
   * Set valid page selector text
   */

  styleSheet = cssom.parse(
"@page CompanyLetterHead {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  cssRule.setSelectorText(":first");
  assertEquals(std::string(":first"), cssRule.selectorText());



  /**
   * Try to set invalid page selector text
   */

  styleSheet = cssom.parse(
"@page CompanyLetterHead {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assert(errors.syntaxErrors == 0);
  cssRule.setSelectorText("&:first");
  assertEquals(std::string("CompanyLetterHead"), cssRule.selectorText());
  assert(errors.syntaxErrors == 1);


  /**
   * Try to set invalid page selector text, which is valid for generic
   * selector.
   */

  styleSheet = cssom.parse(
"@page CompanyLetterHead {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  assert(errors.syntaxErrors == 1);
  cssRule.setSelectorText("h1, h2, h3");
  assertEquals(std::string("CompanyLetterHead"), cssRule.selectorText());
  assert(errors.syntaxErrors == 2);


}



void selector() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet;
  cssom::CSSPageRule cssRule;

  styleSheet = cssom.parse(
"@page :left {\n"
" color : green\n"
"}\n"
  );

  cssRule = cssom::CSSPageRule::cast(
    styleSheet.cssRules()[0]);

  cssom::Selector selector = cssRule.selector();

  selectorText = ":left";
  assertEquals(selectorText, selector.selectorText());
}



} // unnamed

namespace test {



void cssPageRule() {
  cssText();
  selectorText();
  selector();
}



} // test
