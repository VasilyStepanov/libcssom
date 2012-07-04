#include "test_CSSProperty_display.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



cssom::CSSStyleDeclaration getStyleDeclaration(const cssom::CSSOM &cssom) {
  return cssom::CSSStyleRule::cast(cssom.parse("p {}").cssRules()[0]).style();
}



void display() {
  
  /**
   * inline | block | list-item | inline-block | table | inline-table |
   *  table-row-group | table-header-group | table-footer-group | table-row |
   *  table-column-group | table-column | table-cell | table-caption | none |
   *  inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.display() == NULL);



  /**
   * inline | block | list-item | inline-block | table | inline-table |
   *  table-row-group | table-header-group | table-footer-group | table-row |
   *  table-column-group | table-column | table-cell | table-caption | none
   */

  style.setDisplay(NULL);
  style.setDisplay("inline");
  assertEquals(std::string("inline"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("block");
  assertEquals(std::string("block"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("list-item");
  assertEquals(std::string("list-item"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("inline-block");
  assertEquals(std::string("inline-block"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table");
  assertEquals(std::string("table"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("inline-table");
  assertEquals(std::string("inline-table"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-row-group");
  assertEquals(std::string("table-row-group"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-header-group");
  assertEquals(std::string("table-header-group"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-footer-group");
  assertEquals(std::string("table-footer-group"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-row");
  assertEquals(std::string("table-row"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-column-group");
  assertEquals(std::string("table-column-group"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-column");
  assertEquals(std::string("table-column"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-cell");
  assertEquals(std::string("table-cell"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("table-caption");
  assertEquals(std::string("table-caption"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("none");
  assertEquals(std::string("none"), style.display());



  /**
   * inherit
   */

  style.setDisplay(NULL);
  style.setDisplay("inherit");
  assertEquals(std::string("inherit"), style.display());

  style.setDisplay(NULL);
  style.setDisplay("INHERIT");
  assertEquals(std::string("inherit"), style.display());



  /**
   * errors
   */

  style.setDisplay(NULL);
  style.setDisplay("invalid");
  assert(style.display() == NULL);
}



} // unnamed

namespace test {



void cssPropertyDisplay() {
  display();
}



} // test
