#include "test_CSSProperty_azimuth.hpp"

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



void azimuth() {

  /**
   * <angle> | [[ left-side | far-left | left | center-left | center |
   *  center-right | right | far-right | right-side ] || behind ] | leftwards |
   *  rightwards | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.azimuth() == NULL);



  /**
   * angle
   */

  style.setAzimuth(NULL);
  style.setAzimuth("180deg");
  assertEquals(std::string("180deg"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("180.1deg");
  assertEquals(std::string("180.1deg"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("-180DEG");
  assertEquals(std::string("180deg"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("3.14rad");
  assertEquals(std::string("3.14rad"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("-3.14RAD");
  assertEquals(std::string("3.14319rad"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("200grad");
  assertEquals(std::string("200grad"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("200.1grad");
  assertEquals(std::string("200.1grad"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("-200GRAD");
  assertEquals(std::string("200grad"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("-200GRAD");
  assertEquals(std::string("200grad"), style.azimuth());



  /**
   * left-side
   */

  style.setAzimuth(NULL);
  style.setAzimuth("left-side");
  assertEquals(std::string("left-side"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("LEFT-SIDE");
  assertEquals(std::string("left-side"), style.azimuth());



  /**
   * left-side behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("left-side behind");
  assertEquals(std::string("left-side behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind left-side");
  assertEquals(std::string("behind left-side"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND LEFT-SIDE");
  assertEquals(std::string("behind left-side"), style.azimuth());



  /**
   * far-left
   */

  style.setAzimuth(NULL);
  style.setAzimuth("far-left");
  assertEquals(std::string("far-left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("FAR-LEFT");
  assertEquals(std::string("far-left"), style.azimuth());



  /**
   * far-left behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("far-left behind");
  assertEquals(std::string("far-left behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind far-left");
  assertEquals(std::string("behind far-left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND FAR-LEFT");
  assertEquals(std::string("behind far-left"), style.azimuth());



  /**
   * left
   */

  style.setAzimuth(NULL);
  style.setAzimuth("left");
  assertEquals(std::string("left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("LEFT");
  assertEquals(std::string("left"), style.azimuth());



  /**
   * left behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("left behind");
  assertEquals(std::string("left behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind left");
  assertEquals(std::string("behind left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND LEFT");
  assertEquals(std::string("behind left"), style.azimuth());



  /**
   * center-left
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center-left");
  assertEquals(std::string("center-left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("CENTER-LEFT");
  assertEquals(std::string("center-left"), style.azimuth());



  /**
   * center-left behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center-left behind");
  assertEquals(std::string("center-left behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind center-left");
  assertEquals(std::string("behind center-left"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND CENTER-LEFT");
  assertEquals(std::string("behind center-left"), style.azimuth());



  /**
   * center
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center");
  assertEquals(std::string("center"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("CENTER");
  assertEquals(std::string("center"), style.azimuth());



  /**
   * center behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center behind");
  assertEquals(std::string("center behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind center");
  assertEquals(std::string("behind center"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND CENTER");
  assertEquals(std::string("behind center"), style.azimuth());



  /**
   * center-right
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center-right");
  assertEquals(std::string("center-right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("CENTER-RIGHT");
  assertEquals(std::string("center-right"), style.azimuth());



  /**
   * center-right behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("center-right behind");
  assertEquals(std::string("center-right behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind center-right");
  assertEquals(std::string("behind center-right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND CENTER-RIGHT");
  assertEquals(std::string("behind center-right"), style.azimuth());



  /**
   * right
   */

  style.setAzimuth(NULL);
  style.setAzimuth("right");
  assertEquals(std::string("right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("RIGHT");
  assertEquals(std::string("right"), style.azimuth());



  /**
   * right behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("right behind");
  assertEquals(std::string("right behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind right");
  assertEquals(std::string("behind right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND RIGHT");
  assertEquals(std::string("behind right"), style.azimuth());



  /**
   * far-right
   */

  style.setAzimuth(NULL);
  style.setAzimuth("far-right");
  assertEquals(std::string("far-right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("FAR-RIGHT");
  assertEquals(std::string("far-right"), style.azimuth());



  /**
   * far-right behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("far-right behind");
  assertEquals(std::string("far-right behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind far-right");
  assertEquals(std::string("behind far-right"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND FAR-RIGHT");
  assertEquals(std::string("behind far-right"), style.azimuth());



  /**
   * right-side
   */

  style.setAzimuth(NULL);
  style.setAzimuth("right-side");
  assertEquals(std::string("right-side"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("RIGHT-SIDE");
  assertEquals(std::string("right-side"), style.azimuth());



  /**
   * right-side behind
   */

  style.setAzimuth(NULL);
  style.setAzimuth("right-side behind");
  assertEquals(std::string("right-side behind"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("behind right-side");
  assertEquals(std::string("behind right-side"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("BEHIND RIGHT-SIDE");
  assertEquals(std::string("behind right-side"), style.azimuth());



  /**
   * leftwards
   */

  style.setAzimuth(NULL);
  style.setAzimuth("leftwards");
  assertEquals(std::string("leftwards"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("LEFTWARDS");
  assertEquals(std::string("leftwards"), style.azimuth());



  /**
   * rightwards
   */

  style.setAzimuth(NULL);
  style.setAzimuth("rightwards");
  assertEquals(std::string("rightwards"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("RIGHTWARDS");
  assertEquals(std::string("rightwards"), style.azimuth());



  /**
   * inherit
   */

  style.setAzimuth(NULL);
  style.setAzimuth("inherit");
  assertEquals(std::string("inherit"), style.azimuth());

  style.setAzimuth(NULL);
  style.setAzimuth("INHERIT");
  assertEquals(std::string("inherit"), style.azimuth());



  /**
   * errors
   */

  style.setAzimuth(NULL);
  style.setAzimuth("invalid");
  assert(style.azimuth() == NULL);

  style.setAzimuth(NULL);
  style.setAzimuth("left-side behind inherit");
  assert(style.azimuth() == NULL);

  style.setAzimuth(NULL);
  style.setAzimuth("leftwards behind");
  assert(style.azimuth() == NULL);
}



} // unnamed

namespace test {



void cssPropertyAzimuth() {
  azimuth();
}



} // test
