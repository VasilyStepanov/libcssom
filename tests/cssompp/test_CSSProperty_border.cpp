#include "test_CSSProperty_border.hpp"

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



void borderCollapse() {

  /**
   * collapse | separate | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderCollapse() == NULL);



  /**
   * collapse
   */

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("collapse");
  assertEquals(std::string("collapse"), style.borderCollapse());

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("COLLAPSE");
  assertEquals(std::string("collapse"), style.borderCollapse());



  /**
   * separate
   */

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("separate");
  assertEquals(std::string("separate"), style.borderCollapse());

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("SEPARATE");
  assertEquals(std::string("separate"), style.borderCollapse());



  /**
   * inherit
   */

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("inherit");
  assertEquals(std::string("inherit"), style.borderCollapse());

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("INHERIT");
  assertEquals(std::string("inherit"), style.borderCollapse());



  /**
   * errors
   */

  style.setBorderCollapse(NULL);
  style.setBorderCollapse("invalid");
  assert(style.borderCollapse() == NULL);
}



void borderSpacing() {

  /**
   * <length> <length>? | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderSpacing() == NULL);



  /**
   * <length>
   */

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("50px");
  assertEquals(std::string("50px"), style.borderSpacing());

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("0");
  assertEquals(std::string("0"), style.borderSpacing());

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("50PX");
  assertEquals(std::string("50px"), style.borderSpacing());



  /**
   * <length> <length>
   */

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("40px 60px");
  assertEquals(std::string("40px 60px"), style.borderSpacing());

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("0 0");
  assertEquals(std::string("0 0"), style.borderSpacing());



  /**
   * inherit
   */

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("inherit");
  assertEquals(std::string("inherit"), style.borderSpacing());

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("INHERIT");
  assertEquals(std::string("inherit"), style.borderSpacing());



  /**
   * errors
   */

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("invalid");
  assert(style.borderSpacing() == NULL);

  style.setBorderSpacing(NULL);
  style.setBorderSpacing("1");
  assert(style.borderSpacing() == NULL);
}



void borderTopColor() {

  /**
   * <color> | transparent | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderTopColor() == NULL);



  /**
   * <color>
   */

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("red");
  assertEquals(std::string("red"), style.borderTopColor());

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("#800000");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderTopColor());

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("rgb(128, 0, 0)");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderTopColor());



  /**
   * transparent
   */

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("transparent");
  assertEquals(std::string("transparent"), style.borderTopColor());

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("TRANSPARENT");
  assertEquals(std::string("transparent"), style.borderTopColor());



  /**
   * inherit
   */

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("inherit");
  assertEquals(std::string("inherit"), style.borderTopColor());

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("INHERIT");
  assertEquals(std::string("inherit"), style.borderTopColor());



  /**
   * errors
   */

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("invalid");
  assert(style.borderTopColor() == NULL);

  style.setBorderTopColor(NULL);
  style.setBorderTopColor("rgb(256, 0, 0)");
  assert(style.borderTopColor() == NULL);
}



void borderRightColor() {

  /**
   * <color> | transparent | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderRightColor() == NULL);



  /**
   * <color>
   */

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("red");
  assertEquals(std::string("red"), style.borderRightColor());

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("#800000");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderRightColor());

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("rgb(128, 0, 0)");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderRightColor());



  /**
   * transparent
   */

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("transparent");
  assertEquals(std::string("transparent"), style.borderRightColor());

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("TRANSPARENT");
  assertEquals(std::string("transparent"), style.borderRightColor());



  /**
   * inherit
   */

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("inherit");
  assertEquals(std::string("inherit"), style.borderRightColor());

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("INHERIT");
  assertEquals(std::string("inherit"), style.borderRightColor());



  /**
   * errors
   */

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("invalid");
  assert(style.borderRightColor() == NULL);

  style.setBorderRightColor(NULL);
  style.setBorderRightColor("rgb(256, 0, 0)");
  assert(style.borderRightColor() == NULL);
}



void borderBottomColor() {

  /**
   * <color> | transparent | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderBottomColor() == NULL);



  /**
   * <color>
   */

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("red");
  assertEquals(std::string("red"), style.borderBottomColor());

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("#800000");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderBottomColor());

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("rgb(128, 0, 0)");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderBottomColor());



  /**
   * transparent
   */

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("transparent");
  assertEquals(std::string("transparent"), style.borderBottomColor());

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("TRANSPARENT");
  assertEquals(std::string("transparent"), style.borderBottomColor());



  /**
   * inherit
   */

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("inherit");
  assertEquals(std::string("inherit"), style.borderBottomColor());

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("INHERIT");
  assertEquals(std::string("inherit"), style.borderBottomColor());



  /**
   * errors
   */

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("invalid");
  assert(style.borderBottomColor() == NULL);

  style.setBorderBottomColor(NULL);
  style.setBorderBottomColor("rgb(256, 0, 0)");
  assert(style.borderBottomColor() == NULL);
}



void borderLeftColor() {

  /**
   * <color> | transparent | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderLeftColor() == NULL);



  /**
   * <color>
   */

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("red");
  assertEquals(std::string("red"), style.borderLeftColor());

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("#800000");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderLeftColor());

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("rgb(128, 0, 0)");
  assertEquals(std::string("rgb(128, 0, 0)"), style.borderLeftColor());



  /**
   * transparent
   */

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("transparent");
  assertEquals(std::string("transparent"), style.borderLeftColor());

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("TRANSPARENT");
  assertEquals(std::string("transparent"), style.borderLeftColor());



  /**
   * inherit
   */

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("inherit");
  assertEquals(std::string("inherit"), style.borderLeftColor());

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("INHERIT");
  assertEquals(std::string("inherit"), style.borderLeftColor());



  /**
   * errors
   */

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("invalid");
  assert(style.borderLeftColor() == NULL);

  style.setBorderLeftColor(NULL);
  style.setBorderLeftColor("rgb(256, 0, 0)");
  assert(style.borderLeftColor() == NULL);
}



void borderColor() {

  /**
   * [ <color> | transparent ]{1,4} | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderColor() == NULL);



  /**
   * <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red");
  assertEquals(std::string("red red red red"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("red"), style.borderRightColor());
  assertEquals(std::string("red"), style.borderBottomColor());
  assertEquals(std::string("red"), style.borderLeftColor());



  /**
   * <color> <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red green");
  assertEquals(std::string("red green red green"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("green"), style.borderRightColor());
  assertEquals(std::string("red"), style.borderBottomColor());
  assertEquals(std::string("green"), style.borderLeftColor());



  /**
   * <color> <color> <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red green blue");
  assertEquals(std::string("red green blue green"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("green"), style.borderRightColor());
  assertEquals(std::string("blue"), style.borderBottomColor());
  assertEquals(std::string("green"), style.borderLeftColor());



  /**
   * <color> <color> <color> <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red green blue yellow");
  assertEquals(std::string("red green blue yellow"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("green"), style.borderRightColor());
  assertEquals(std::string("blue"), style.borderBottomColor());
  assertEquals(std::string("yellow"), style.borderLeftColor());



  /**
   * inherit
   */

  style.setBorderColor(NULL);
  style.setBorderColor("inherit");
  assertEquals(std::string("inherit"), style.borderColor());
  assertEquals(std::string("inherit"), style.borderTopColor());
  assertEquals(std::string("inherit"), style.borderRightColor());
  assertEquals(std::string("inherit"), style.borderBottomColor());
  assertEquals(std::string("inherit"), style.borderLeftColor());



  /**
   * errors
   */

  style.setBorderColor(NULL);
  style.setBorderColor("invalid");
  assert(style.borderColor() == NULL);
}



} // unnamed

namespace test {



void cssPropertyBorder() {
  borderCollapse();
  borderSpacing();
  borderTopColor();
  borderRightColor();
  borderBottomColor();
  borderLeftColor();
  borderColor();
}



} // test
