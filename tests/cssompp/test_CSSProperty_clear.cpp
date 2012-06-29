#include "test_CSSProperty_clear.hpp"

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



void clear() {
  
  /**
   * none | left | right | both | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.clear() == NULL);



  /**
   * none
   */

  style.setClear(NULL);
  style.setClear("none");
  assertEquals(std::string("none"), style.clear());

  style.setClear(NULL);
  style.setClear("NONE");
  assertEquals(std::string("none"), style.clear());



  /**
   * left
   */

  style.setClear(NULL);
  style.setClear("left");
  assertEquals(std::string("left"), style.clear());

  style.setClear(NULL);
  style.setClear("LEFT");
  assertEquals(std::string("left"), style.clear());



  /**
   * right
   */

  style.setClear(NULL);
  style.setClear("right");
  assertEquals(std::string("right"), style.clear());

  style.setClear(NULL);
  style.setClear("RIGHT");
  assertEquals(std::string("right"), style.clear());



  /**
   * both
   */

  style.setClear(NULL);
  style.setClear("both");
  assertEquals(std::string("both"), style.clear());

  style.setClear(NULL);
  style.setClear("BOTH");
  assertEquals(std::string("both"), style.clear());



  /**
   * inherit
   */

  style.setClear(NULL);
  style.setClear("inherit");
  assertEquals(std::string("inherit"), style.clear());

  style.setClear(NULL);
  style.setClear("INHERIT");
  assertEquals(std::string("inherit"), style.clear());



  /**
   * errors
   */

  style.setClear(NULL);
  style.setClear("invalid");
  assert(style.clear() == NULL);
}



} // unnamed

namespace test {



void cssPropertyClear() {
  clear();
}



} // test
