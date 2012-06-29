#include "test_CSSProperty_color.hpp"

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



void color() {
  
  /**
   * <color> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.color() == NULL);



  /**
   * <color>
   */

  style.setColor(NULL);
  style.setColor("red");
  assertEquals(std::string("red"), style.color());

  style.setColor(NULL);
  style.setColor("#800000");
  assertEquals(std::string("rgb(128, 0, 0)"), style.color());

  style.setColor(NULL);
  style.setColor("rgb(128, 0, 0)");
  assertEquals(std::string("rgb(128, 0, 0)"), style.color());



  /**
   * inherit
   */

  style.setColor(NULL);
  style.setColor("inherit");
  assertEquals(std::string("inherit"), style.color());

  style.setColor(NULL);
  style.setColor("INHERIT");
  assertEquals(std::string("inherit"), style.color());



  /**
   * errors
   */

  style.setColor(NULL);
  style.setColor("invalid");
  assert(style.color() == NULL);

  style.setColor(NULL);
  style.setColor("rect(1px, 1px, 1px, 1px, 1px)");
  assert(style.color() == NULL);

  style.setColor(NULL);
  style.setColor("rgb(256, 0, 0)");
  assert(style.color() == NULL);
}



} // unnamed

namespace test {



void cssPropertyColor() {
  color();
}



} // test
