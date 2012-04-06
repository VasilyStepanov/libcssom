#include "test_CSSPageRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



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
  selectorText();
}



} // test
