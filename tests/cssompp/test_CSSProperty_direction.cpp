#include "test_CSSProperty_direction.hpp"

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



void direction() {
  
  /**
   * ltr | rtl | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.direction() == NULL);



  /**
   * ltr
   */

  style.setDirection(NULL);
  style.setDirection("ltr");
  assertEquals(std::string("ltr"), style.direction());

  style.setDirection(NULL);
  style.setDirection("LTR");
  assertEquals(std::string("ltr"), style.direction());



  /**
   * rtl   
   */

  style.setDirection(NULL);
  style.setDirection("rtl");
  assertEquals(std::string("rtl"), style.direction());

  style.setDirection(NULL);
  style.setDirection("RTL");
  assertEquals(std::string("rtl"), style.direction());



  /**
   * inherit
   */

  style.setDirection(NULL);
  style.setDirection("inherit");
  assertEquals(std::string("inherit"), style.direction());

  style.setDirection(NULL);
  style.setDirection("INHERIT");
  assertEquals(std::string("inherit"), style.direction());



  /**
   * errors
   */

  style.setDirection(NULL);
  style.setDirection("invalid");
  assert(style.direction() == NULL);
}



} // unnamed

namespace test {



void cssPropertyDirection() {
  direction();
}



} // test
