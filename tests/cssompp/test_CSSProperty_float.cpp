#include "test_CSSProperty_float.hpp"

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



void cssFloat() {
  
  /**
   * left | right | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cssFloat() == NULL);



  /**
   * left | right | none
   */

  style.setCSSFloat(NULL);
  style.setCSSFloat("left");
  assertEquals(std::string("left"), style.cssFloat());

  style.setCSSFloat(NULL);
  style.setCSSFloat("right");
  assertEquals(std::string("right"), style.cssFloat());

  style.setCSSFloat(NULL);
  style.setCSSFloat("none");
  assertEquals(std::string("none"), style.cssFloat());

  style.setCSSFloat(NULL);
  style.setCSSFloat("LEFT");
  assertEquals(std::string("left"), style.cssFloat());



  /**
   * inherit
   */

  style.setCSSFloat(NULL);
  style.setCSSFloat("inherit");
  assertEquals(std::string("inherit"), style.cssFloat());

  style.setCSSFloat(NULL);
  style.setCSSFloat("INHERIT");
  assertEquals(std::string("inherit"), style.cssFloat());



  /**
   * errors
   */

  style.setCSSFloat(NULL);
  style.setCSSFloat("invalid");
  assert(style.cssFloat() == NULL);
}



} // unnamed

namespace test {



void cssPropertyFloat() {
  cssFloat();
}



} // test
