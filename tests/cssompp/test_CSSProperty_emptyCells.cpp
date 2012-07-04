#include "test_CSSProperty_emptyCells.hpp"

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



void emptyCells() {
  
  /**
   * show | hide | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.emptyCells() == NULL);



  /**
   * show | hide
   */

  style.setEmptyCells(NULL);
  style.setEmptyCells("show");
  assertEquals(std::string("show"), style.emptyCells());

  style.setEmptyCells(NULL);
  style.setEmptyCells("hide");
  assertEquals(std::string("hide"), style.emptyCells());

  style.setEmptyCells(NULL);
  style.setEmptyCells("SHOW");
  assertEquals(std::string("show"), style.emptyCells());



  /**
   * inherit
   */

  style.setEmptyCells(NULL);
  style.setEmptyCells("inherit");
  assertEquals(std::string("inherit"), style.emptyCells());

  style.setEmptyCells(NULL);
  style.setEmptyCells("INHERIT");
  assertEquals(std::string("inherit"), style.emptyCells());



  /**
   * errors
   */

  style.setEmptyCells(NULL);
  style.setEmptyCells("invalid");
  assert(style.emptyCells() == NULL);
}



} // unnamed

namespace test {



void cssPropertyEmptyCells() {
  emptyCells();
}



} // test
