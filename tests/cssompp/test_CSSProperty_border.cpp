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
  assertEquals(std::string("red"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("red"), style.borderRightColor());
  assertEquals(std::string("red"), style.borderBottomColor());
  assertEquals(std::string("red"), style.borderLeftColor());



  /**
   * <color> <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red green");
  assertEquals(std::string("red green"), style.borderColor());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("green"), style.borderRightColor());
  assertEquals(std::string("red"), style.borderBottomColor());
  assertEquals(std::string("green"), style.borderLeftColor());



  /**
   * <color> <color> <color>
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red green blue");
  assertEquals(std::string("red green blue"), style.borderColor());
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



void borderTopStyle() {

  /**
   * <border-style> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderTopStyle() == NULL);



  /**
   * <border-style>
   */

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("none");
  assertEquals(std::string("none"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("hidden");
  assertEquals(std::string("hidden"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("dotted");
  assertEquals(std::string("dotted"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("dashed");
  assertEquals(std::string("dashed"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("solid");
  assertEquals(std::string("solid"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("double");
  assertEquals(std::string("double"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("groove");
  assertEquals(std::string("groove"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("ridge");
  assertEquals(std::string("ridge"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("inset");
  assertEquals(std::string("inset"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("outset");
  assertEquals(std::string("outset"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("NONE");
  assertEquals(std::string("none"), style.borderTopStyle());



  /**
   * inherit
   */

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("inherit");
  assertEquals(std::string("inherit"), style.borderTopStyle());

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("INHERIT");
  assertEquals(std::string("inherit"), style.borderTopStyle());



  /**
   * errors
   */

  style.setBorderTopStyle(NULL);
  style.setBorderTopStyle("invalid");
  assert(style.borderTopStyle() == NULL);
}



void borderRightStyle() {

  /**
   * <border-style> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderRightStyle() == NULL);



  /**
   * <border-style>
   */

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("none");
  assertEquals(std::string("none"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("hidden");
  assertEquals(std::string("hidden"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("dotted");
  assertEquals(std::string("dotted"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("dashed");
  assertEquals(std::string("dashed"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("solid");
  assertEquals(std::string("solid"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("double");
  assertEquals(std::string("double"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("groove");
  assertEquals(std::string("groove"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("ridge");
  assertEquals(std::string("ridge"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("inset");
  assertEquals(std::string("inset"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("outset");
  assertEquals(std::string("outset"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("NONE");
  assertEquals(std::string("none"), style.borderRightStyle());



  /**
   * inherit
   */

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("inherit");
  assertEquals(std::string("inherit"), style.borderRightStyle());

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("INHERIT");
  assertEquals(std::string("inherit"), style.borderRightStyle());



  /**
   * errors
   */

  style.setBorderRightStyle(NULL);
  style.setBorderRightStyle("invalid");
  assert(style.borderRightStyle() == NULL);
}



void borderBottomStyle() {

  /**
   * <border-style> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderBottomStyle() == NULL);



  /**
   * <border-style>
   */

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("none");
  assertEquals(std::string("none"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("hidden");
  assertEquals(std::string("hidden"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("dotted");
  assertEquals(std::string("dotted"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("dashed");
  assertEquals(std::string("dashed"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("solid");
  assertEquals(std::string("solid"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("double");
  assertEquals(std::string("double"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("groove");
  assertEquals(std::string("groove"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("ridge");
  assertEquals(std::string("ridge"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("inset");
  assertEquals(std::string("inset"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("outset");
  assertEquals(std::string("outset"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("NONE");
  assertEquals(std::string("none"), style.borderBottomStyle());



  /**
   * inherit
   */

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("inherit");
  assertEquals(std::string("inherit"), style.borderBottomStyle());

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("INHERIT");
  assertEquals(std::string("inherit"), style.borderBottomStyle());



  /**
   * errors
   */

  style.setBorderBottomStyle(NULL);
  style.setBorderBottomStyle("invalid");
  assert(style.borderBottomStyle() == NULL);
}



void borderLeftStyle() {

  /**
   * <border-style> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderLeftStyle() == NULL);



  /**
   * <border-style>
   */

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("none");
  assertEquals(std::string("none"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("hidden");
  assertEquals(std::string("hidden"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("dotted");
  assertEquals(std::string("dotted"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("dashed");
  assertEquals(std::string("dashed"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("solid");
  assertEquals(std::string("solid"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("double");
  assertEquals(std::string("double"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("groove");
  assertEquals(std::string("groove"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("ridge");
  assertEquals(std::string("ridge"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("inset");
  assertEquals(std::string("inset"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("outset");
  assertEquals(std::string("outset"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("NONE");
  assertEquals(std::string("none"), style.borderLeftStyle());



  /**
   * inherit
   */

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("inherit");
  assertEquals(std::string("inherit"), style.borderLeftStyle());

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("INHERIT");
  assertEquals(std::string("inherit"), style.borderLeftStyle());



  /**
   * errors
   */

  style.setBorderLeftStyle(NULL);
  style.setBorderLeftStyle("invalid");
  assert(style.borderLeftStyle() == NULL);
}



void borderStyle() {

  /**
   * <border-style>{1,4} | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderStyle() == NULL);



  /**
   * <border-style>
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("none");
  assertEquals(std::string("none"), style.borderStyle());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("none"), style.borderRightStyle());
  assertEquals(std::string("none"), style.borderBottomStyle());
  assertEquals(std::string("none"), style.borderLeftStyle());



  /**
   * <border-style> <border-style>
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("none hidden");
  assertEquals(std::string("none hidden"), style.borderStyle());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("hidden"), style.borderRightStyle());
  assertEquals(std::string("none"), style.borderBottomStyle());
  assertEquals(std::string("hidden"), style.borderLeftStyle());



  /**
   * <border-style> <border-style> <border-style>
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("none hidden dotted");
  assertEquals(std::string("none hidden dotted"), style.borderStyle());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("hidden"), style.borderRightStyle());
  assertEquals(std::string("dotted"), style.borderBottomStyle());
  assertEquals(std::string("hidden"), style.borderLeftStyle());



  /**
   * <border-style> <border-style> <border-style> <border-style>
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("none hidden dotted dashed");
  assertEquals(std::string("none hidden dotted dashed"), style.borderStyle());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("hidden"), style.borderRightStyle());
  assertEquals(std::string("dotted"), style.borderBottomStyle());
  assertEquals(std::string("dashed"), style.borderLeftStyle());



  /**
   * inherit
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("inherit");
  assertEquals(std::string("inherit"), style.borderStyle());
  assertEquals(std::string("inherit"), style.borderTopStyle());
  assertEquals(std::string("inherit"), style.borderRightStyle());
  assertEquals(std::string("inherit"), style.borderBottomStyle());
  assertEquals(std::string("inherit"), style.borderLeftStyle());



  /**
   * errors
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("invalid");
  assert(style.borderStyle() == NULL);
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
  borderTopStyle();
  borderRightStyle();
  borderBottomStyle();
  borderLeftStyle();
  borderStyle();
}



} // test
