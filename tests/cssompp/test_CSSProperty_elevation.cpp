#include "test_CSSProperty_elevation.hpp"

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



void elevation() {
  
  /**
   * <angle> | below | level | above | higher | lower | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.elevation() == NULL);



  /**
   * <angle>
   */

  style.setElevation(NULL);
  style.setElevation("30deg");
  assertEquals(std::string("30deg"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("30DEG");
  assertEquals(std::string("30deg"), style.elevation());



  /**
   * below | level | above | higher | lower
   */

  style.setElevation(NULL);
  style.setElevation("below");
  assertEquals(std::string("below"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("level");
  assertEquals(std::string("level"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("above");
  assertEquals(std::string("above"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("higher");
  assertEquals(std::string("higher"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("lower");
  assertEquals(std::string("lower"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("BELOW");
  assertEquals(std::string("below"), style.elevation());



  /**
   * inherit
   */

  style.setElevation(NULL);
  style.setElevation("inherit");
  assertEquals(std::string("inherit"), style.elevation());

  style.setElevation(NULL);
  style.setElevation("INHERIT");
  assertEquals(std::string("inherit"), style.elevation());



  /**
   * errors
   */

  style.setElevation(NULL);
  style.setElevation("invalid");
  assert(style.elevation() == NULL);



  /**
   * TODO: No idea how to handle this.
   */
  style.setElevation(NULL);
  style.setElevation("91deg");
  assertEquals(std::string("91deg"), style.elevation());
}



} // unnamed

namespace test {



void cssPropertyElevation() {
  elevation();
}



} // test
