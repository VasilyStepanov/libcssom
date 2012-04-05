#include "test_CSSPageRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



/**
@page { color : green }
@page :left { color : green }
@page :right { color : green  }
@page LandscapeTable { color : green }
@page CompanyLetterHead:first { color : green }
 */
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

  assertEquals(std::string("@page"), cssRule.selectorText());



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

  assertEquals(std::string("@page :left"), cssRule.selectorText());



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

  assertEquals(std::string("@page LandscapeTable"), cssRule.selectorText());



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

  assertEquals(std::string("@page CompanyLetterHead:first"),
    cssRule.selectorText());
}



} // unnamed

namespace test {



void cssPageRule() {
  selectorText();
}



} // test
