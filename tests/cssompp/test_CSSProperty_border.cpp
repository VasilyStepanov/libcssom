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

  assert(style.borderColor() != NULL);
  assertEquals(std::string(""), style.borderColor());



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
   * imposible shorthand
   */

  style.setBorderColor(NULL);
  style.setBorderColor("red");
  style.setBorderTopColor("inherit");
  assertEquals(std::string(""), style.borderColor());



  /**
   * errors
   */

  style.setBorderColor(NULL);
  style.setBorderColor("invalid");
  assert(style.borderColor() != NULL);
  assertEquals(std::string(""), style.borderColor());

  style.setBorderColor(NULL);
  style.setBorderColor("inherit inherit inherit inherit");
  assert(style.borderColor() != NULL);
  assertEquals(std::string(""), style.borderColor());
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

  assert(style.borderStyle() != NULL);
  assertEquals(std::string(""), style.borderStyle());



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
   * imposible shorthand
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("none");
  style.setBorderTopStyle("inherit");
  assertEquals(std::string(""), style.borderStyle());



  /**
   * errors
   */

  style.setBorderStyle(NULL);
  style.setBorderStyle("invalid");
  assert(style.borderStyle() != NULL);
  assertEquals(std::string(""), style.borderStyle());

  style.setBorderStyle(NULL);
  style.setBorderStyle("inherit inherit inherit inherit");
  assert(style.borderStyle() != NULL);
  assertEquals(std::string(""), style.borderStyle());
}



void borderTopWidth() {

  /**
   * <border-width> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderTopWidth() == NULL);



  /**
   * <border-width>
   */

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("thin");
  assertEquals(std::string("thin"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("medium");
  assertEquals(std::string("medium"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("thick");
  assertEquals(std::string("thick"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("1px");
  assertEquals(std::string("1px"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("0");
  assertEquals(std::string("0"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("THIN");
  assertEquals(std::string("thin"), style.borderTopWidth());



  /**
   * inherit
   */

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("inherit");
  assertEquals(std::string("inherit"), style.borderTopWidth());

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("INHERIT");
  assertEquals(std::string("inherit"), style.borderTopWidth());



  /**
   * errors
   */

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("invalid");
  assert(style.borderTopWidth() == NULL);

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("-1px");
  assert(style.borderTopWidth() == NULL);

  style.setBorderTopWidth(NULL);
  style.setBorderTopWidth("1");
  assert(style.borderTopWidth() == NULL);
}



void borderRightWidth() {

  /**
   * <border-width> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderRightWidth() == NULL);



  /**
   * <border-width>
   */

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("thin");
  assertEquals(std::string("thin"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("medium");
  assertEquals(std::string("medium"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("thick");
  assertEquals(std::string("thick"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("1px");
  assertEquals(std::string("1px"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("0");
  assertEquals(std::string("0"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("THIN");
  assertEquals(std::string("thin"), style.borderRightWidth());



  /**
   * inherit
   */

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("inherit");
  assertEquals(std::string("inherit"), style.borderRightWidth());

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("INHERIT");
  assertEquals(std::string("inherit"), style.borderRightWidth());



  /**
   * errors
   */

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("invalid");
  assert(style.borderRightWidth() == NULL);

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("-1px");
  assert(style.borderRightWidth() == NULL);

  style.setBorderRightWidth(NULL);
  style.setBorderRightWidth("1");
  assert(style.borderRightWidth() == NULL);
}



void borderBottomWidth() {

  /**
   * <border-width> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderBottomWidth() == NULL);



  /**
   * <border-width>
   */

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("thin");
  assertEquals(std::string("thin"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("medium");
  assertEquals(std::string("medium"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("thick");
  assertEquals(std::string("thick"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("1px");
  assertEquals(std::string("1px"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("0");
  assertEquals(std::string("0"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("THIN");
  assertEquals(std::string("thin"), style.borderBottomWidth());



  /**
   * inherit
   */

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("inherit");
  assertEquals(std::string("inherit"), style.borderBottomWidth());

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("INHERIT");
  assertEquals(std::string("inherit"), style.borderBottomWidth());



  /**
   * errors
   */

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("invalid");
  assert(style.borderBottomWidth() == NULL);

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("-1px");
  assert(style.borderBottomWidth() == NULL);

  style.setBorderBottomWidth(NULL);
  style.setBorderBottomWidth("1");
  assert(style.borderBottomWidth() == NULL);
}



void borderLeftWidth() {

  /**
   * <border-width> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderLeftWidth() == NULL);



  /**
   * <border-width>
   */

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("thin");
  assertEquals(std::string("thin"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("medium");
  assertEquals(std::string("medium"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("thick");
  assertEquals(std::string("thick"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("1px");
  assertEquals(std::string("1px"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("0");
  assertEquals(std::string("0"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("THIN");
  assertEquals(std::string("thin"), style.borderLeftWidth());



  /**
   * inherit
   */

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("inherit");
  assertEquals(std::string("inherit"), style.borderLeftWidth());

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("INHERIT");
  assertEquals(std::string("inherit"), style.borderLeftWidth());



  /**
   * errors
   */

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("invalid");
  assert(style.borderLeftWidth() == NULL);

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("-1px");
  assert(style.borderLeftWidth() == NULL);

  style.setBorderLeftWidth(NULL);
  style.setBorderLeftWidth("1");
  assert(style.borderLeftWidth() == NULL);
}



void borderWidth() {

  /**
   * <border-style>{1,4} | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderWidth() != NULL);
  assertEquals(std::string(""), style.borderWidth());



  /**
   * <border-style>
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("1px");
  assertEquals(std::string("1px"), style.borderWidth());
  assertEquals(std::string("1px"), style.borderTopWidth());
  assertEquals(std::string("1px"), style.borderRightWidth());
  assertEquals(std::string("1px"), style.borderBottomWidth());
  assertEquals(std::string("1px"), style.borderLeftWidth());



  /**
   * <border-style> <border-style>
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("1px 2px");
  assertEquals(std::string("1px 2px"), style.borderWidth());
  assertEquals(std::string("1px"), style.borderTopWidth());
  assertEquals(std::string("2px"), style.borderRightWidth());
  assertEquals(std::string("1px"), style.borderBottomWidth());
  assertEquals(std::string("2px"), style.borderLeftWidth());



  /**
   * <border-style> <border-style> <border-style>
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("1px 2px 3px");
  assertEquals(std::string("1px 2px 3px"), style.borderWidth());
  assertEquals(std::string("1px"), style.borderTopWidth());
  assertEquals(std::string("2px"), style.borderRightWidth());
  assertEquals(std::string("3px"), style.borderBottomWidth());
  assertEquals(std::string("2px"), style.borderLeftWidth());



  /**
   * <border-style> <border-style> <border-style> <border-style>
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("1px 2px 3px 4px");
  assertEquals(std::string("1px 2px 3px 4px"), style.borderWidth());
  assertEquals(std::string("1px"), style.borderTopWidth());
  assertEquals(std::string("2px"), style.borderRightWidth());
  assertEquals(std::string("3px"), style.borderBottomWidth());
  assertEquals(std::string("4px"), style.borderLeftWidth());



  /**
   * inherit
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("inherit");
  assertEquals(std::string("inherit"), style.borderWidth());
  assertEquals(std::string("inherit"), style.borderTopWidth());
  assertEquals(std::string("inherit"), style.borderRightWidth());
  assertEquals(std::string("inherit"), style.borderBottomWidth());
  assertEquals(std::string("inherit"), style.borderLeftWidth());



  /**
   * imposible shorthand
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("1px");
  style.setBorderTopWidth("inherit");
  assertEquals(std::string(""), style.borderWidth());



  /**
   * errors
   */

  style.setBorderWidth(NULL);
  style.setBorderWidth("invalid");
  assert(style.borderWidth() != NULL);
  assertEquals(std::string(""), style.borderWidth());

  style.setBorderWidth(NULL);
  style.setBorderWidth("inherit inherit inherit inherit");
  assert(style.borderWidth() != NULL);
  assertEquals(std::string(""), style.borderWidth());
}



void borderTop() {

  /**
   * [ <border-width> || <border-style> || 'border-top-color' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderTop() != NULL);
  assertEquals(std::string(""), style.borderTop());



  /**
   * <border-width>
   */

  style.setBorderTop(NULL);
  style.setBorderTop("thin");
  assertEquals(std::string("thin"), style.borderTop());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderTopColor());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("thin"), style.borderTopWidth());



  /**
   * <border-style>
   */

  style.setBorderTop(NULL);
  style.setBorderTop("dotted");
  assertEquals(std::string("dotted"), style.borderTop());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderTopColor());
  assertEquals(std::string("dotted"), style.borderTopStyle());
  assertEquals(std::string("medium"), style.borderTopWidth());



  /**
   * 'border-top-color'
   */

  style.setBorderTop(NULL);
  style.setBorderTop("red");
  assertEquals(std::string("red"), style.borderTop());
  assertEquals(std::string("red"), style.borderTopColor());
  assertEquals(std::string("none"), style.borderTopStyle());
  assertEquals(std::string("medium"), style.borderTopWidth());



  /**
   * <border-width> <border-style> 'border-top-color'
   */

  style.setBorderTop(NULL);
  style.setBorderTop("inherit dotted thin");
  assertEquals(std::string("thin dotted inherit"), style.borderTop());
  assertEquals(std::string("inherit"), style.borderTopColor());
  assertEquals(std::string("dotted"), style.borderTopStyle());
  assertEquals(std::string("thin"), style.borderTopWidth());



  /**
   * inherit
   */

  style.setBorderTop(NULL);
  style.setBorderTop("inherit");
  assertEquals(std::string("inherit"), style.borderTop());
  assertEquals(std::string("inherit"), style.borderTopColor());
  assertEquals(std::string("inherit"), style.borderTopStyle());
  assertEquals(std::string("inherit"), style.borderTopWidth());



  /**
   * imposible shorthand
   */

  style.setBorderTop(NULL);
  style.setBorderTop("red");
  style.setBorderTopWidth("inherit");
  assertEquals(std::string(""), style.borderTop());



  /**
   * errors
   */

  style.setBorderTop(NULL);
  style.setBorderTop("invalid");
  assert(style.borderTop() != NULL);
  assertEquals(std::string(""), style.borderTop());

  style.setBorderTop(NULL);
  style.setBorderTop("inherit inherit inherit");
  assert(style.borderTop() != NULL);
  assertEquals(std::string(""), style.borderTop());

  style.setBorderTop(NULL);
  style.setBorderTop("inherit dotted red");
  assert(style.borderTop() != NULL);
  assertEquals(std::string(""), style.borderTop());
}



void borderRight() {

  /**
   * [ <border-width> || <border-style> || 'border-top-color' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderRight() != NULL);
  assertEquals(std::string(""), style.borderRight());



  /**
   * <border-width>
   */

  style.setBorderRight(NULL);
  style.setBorderRight("thin");
  assertEquals(std::string("thin"), style.borderRight());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderRightColor());
  assertEquals(std::string("none"), style.borderRightStyle());
  assertEquals(std::string("thin"), style.borderRightWidth());



  /**
   * <border-style>
   */

  style.setBorderRight(NULL);
  style.setBorderRight("dotted");
  assertEquals(std::string("dotted"), style.borderRight());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderRightColor());
  assertEquals(std::string("dotted"), style.borderRightStyle());
  assertEquals(std::string("medium"), style.borderRightWidth());



  /**
   * 'border-top-color'
   */

  style.setBorderRight(NULL);
  style.setBorderRight("red");
  assertEquals(std::string("red"), style.borderRight());
  assertEquals(std::string("red"), style.borderRightColor());
  assertEquals(std::string("none"), style.borderRightStyle());
  assertEquals(std::string("medium"), style.borderRightWidth());



  /**
   * <border-width> <border-style> 'border-top-color'
   */

  style.setBorderRight(NULL);
  style.setBorderRight("inherit dotted thin");
  assertEquals(std::string("thin dotted inherit"), style.borderRight());
  assertEquals(std::string("inherit"), style.borderRightColor());
  assertEquals(std::string("dotted"), style.borderRightStyle());
  assertEquals(std::string("thin"), style.borderRightWidth());



  /**
   * inherit
   */

  style.setBorderRight(NULL);
  style.setBorderRight("inherit");
  assertEquals(std::string("inherit"), style.borderRight());
  assertEquals(std::string("inherit"), style.borderRightColor());
  assertEquals(std::string("inherit"), style.borderRightStyle());
  assertEquals(std::string("inherit"), style.borderRightWidth());



  /**
   * imposible shorthand
   */

  style.setBorderRight(NULL);
  style.setBorderRight("red");
  style.setBorderRightWidth("inherit");
  assertEquals(std::string(""), style.borderRight());



  /**
   * errors
   */

  style.setBorderRight(NULL);
  style.setBorderRight("invalid");
  assert(style.borderRight() != NULL);
  assertEquals(std::string(""), style.borderRight());

  style.setBorderRight(NULL);
  style.setBorderRight("inherit inherit inherit");
  assert(style.borderRight() != NULL);
  assertEquals(std::string(""), style.borderRight());

  style.setBorderRight(NULL);
  style.setBorderRight("inherit dotted red");
  assert(style.borderRight() != NULL);
  assertEquals(std::string(""), style.borderRight());
}



void borderBottom() {

  /**
   * [ <border-width> || <border-style> || 'border-top-color' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderBottom() != NULL);
  assertEquals(std::string(""), style.borderBottom());



  /**
   * <border-width>
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("thin");
  assertEquals(std::string("thin"), style.borderBottom());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderBottomColor());
  assertEquals(std::string("none"), style.borderBottomStyle());
  assertEquals(std::string("thin"), style.borderBottomWidth());



  /**
   * <border-style>
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("dotted");
  assertEquals(std::string("dotted"), style.borderBottom());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderBottomColor());
  assertEquals(std::string("dotted"), style.borderBottomStyle());
  assertEquals(std::string("medium"), style.borderBottomWidth());



  /**
   * 'border-top-color'
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("red");
  assertEquals(std::string("red"), style.borderBottom());
  assertEquals(std::string("red"), style.borderBottomColor());
  assertEquals(std::string("none"), style.borderBottomStyle());
  assertEquals(std::string("medium"), style.borderBottomWidth());



  /**
   * <border-width> <border-style> 'border-top-color'
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("inherit dotted thin");
  assertEquals(std::string("thin dotted inherit"), style.borderBottom());
  assertEquals(std::string("inherit"), style.borderBottomColor());
  assertEquals(std::string("dotted"), style.borderBottomStyle());
  assertEquals(std::string("thin"), style.borderBottomWidth());



  /**
   * inherit
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("inherit");
  assertEquals(std::string("inherit"), style.borderBottom());
  assertEquals(std::string("inherit"), style.borderBottomColor());
  assertEquals(std::string("inherit"), style.borderBottomStyle());
  assertEquals(std::string("inherit"), style.borderBottomWidth());



  /**
   * imposible shorthand
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("red");
  style.setBorderBottomWidth("inherit");
  assertEquals(std::string(""), style.borderBottom());



  /**
   * errors
   */

  style.setBorderBottom(NULL);
  style.setBorderBottom("invalid");
  assert(style.borderBottom() != NULL);
  assertEquals(std::string(""), style.borderBottom());

  style.setBorderBottom(NULL);
  style.setBorderBottom("inherit inherit inherit");
  assert(style.borderBottom() != NULL);
  assertEquals(std::string(""), style.borderBottom());

  style.setBorderBottom(NULL);
  style.setBorderBottom("inherit dotted red");
  assert(style.borderBottom() != NULL);
  assertEquals(std::string(""), style.borderBottom());
}



void borderLeft() {

  /**
   * [ <border-width> || <border-style> || 'border-top-color' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.borderLeft() != NULL);
  assertEquals(std::string(""), style.borderLeft());



  /**
   * <border-width>
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("thin");
  assertEquals(std::string("thin"), style.borderLeft());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderLeftColor());
  assertEquals(std::string("none"), style.borderLeftStyle());
  assertEquals(std::string("thin"), style.borderLeftWidth());



  /**
   * <border-style>
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("dotted");
  assertEquals(std::string("dotted"), style.borderLeft());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderLeftColor());
  assertEquals(std::string("dotted"), style.borderLeftStyle());
  assertEquals(std::string("medium"), style.borderLeftWidth());



  /**
   * 'border-top-color'
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("red");
  assertEquals(std::string("red"), style.borderLeft());
  assertEquals(std::string("red"), style.borderLeftColor());
  assertEquals(std::string("none"), style.borderLeftStyle());
  assertEquals(std::string("medium"), style.borderLeftWidth());



  /**
   * <border-width> <border-style> 'border-top-color'
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("inherit dotted thin");
  assertEquals(std::string("thin dotted inherit"), style.borderLeft());
  assertEquals(std::string("inherit"), style.borderLeftColor());
  assertEquals(std::string("dotted"), style.borderLeftStyle());
  assertEquals(std::string("thin"), style.borderLeftWidth());



  /**
   * inherit
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("inherit");
  assertEquals(std::string("inherit"), style.borderLeft());
  assertEquals(std::string("inherit"), style.borderLeftColor());
  assertEquals(std::string("inherit"), style.borderLeftStyle());
  assertEquals(std::string("inherit"), style.borderLeftWidth());



  /**
   * imposible shorthand
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("red");
  style.setBorderLeftWidth("inherit");
  assertEquals(std::string(""), style.borderLeft());



  /**
   * errors
   */

  style.setBorderLeft(NULL);
  style.setBorderLeft("invalid");
  assert(style.borderLeft() != NULL);
  assertEquals(std::string(""), style.borderLeft());

  style.setBorderLeft(NULL);
  style.setBorderLeft("inherit inherit inherit");
  assert(style.borderLeft() != NULL);
  assertEquals(std::string(""), style.borderLeft());

  style.setBorderLeft(NULL);
  style.setBorderLeft("inherit dotted red");
  assert(style.borderLeft() != NULL);
  assertEquals(std::string(""), style.borderLeft());
}



void border() {

  /**
   * [ <border-width> || <border-style> || 'border-top-color' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.border() != NULL);
  assertEquals(std::string(""), style.border());



  /**
   * <border-width>
   */

  style.setBorder(NULL);
  style.setBorder("thin");
  assertEquals(std::string("thin"), style.border());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderColor());
  assertEquals(std::string("none"), style.borderStyle());
  assertEquals(std::string("thin"), style.borderWidth());



  /**
   * <border-style>
   */

  style.setBorder(NULL);
  style.setBorder("dotted");
  assertEquals(std::string("dotted"), style.border());
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderColor());
  assertEquals(std::string("dotted"), style.borderStyle());
  assertEquals(std::string("medium"), style.borderWidth());



  /**
   * 'border-top-color'
   */

  style.setBorder(NULL);
  style.setBorder("red");
  assertEquals(std::string("red"), style.border());
  assertEquals(std::string("red"), style.borderColor());
  assertEquals(std::string("none"), style.borderStyle());
  assertEquals(std::string("medium"), style.borderWidth());



  /**
   * <border-width> <border-style> 'border-top-color'
   */

  style.setBorder(NULL);
  style.setBorder("inherit dotted thin");
  assertEquals(std::string("thin dotted inherit"), style.border());
  assertEquals(std::string("inherit"), style.borderColor());
  assertEquals(std::string("dotted"), style.borderStyle());
  assertEquals(std::string("thin"), style.borderWidth());



  /**
   * inherit
   */

  style.setBorder(NULL);
  style.setBorder("inherit");
  assertEquals(std::string("inherit"), style.border());
  assertEquals(std::string("inherit"), style.borderColor());
  assertEquals(std::string("inherit"), style.borderStyle());
  assertEquals(std::string("inherit"), style.borderWidth());



  /**
   * imposible shorthand
   */

  style.setBorder(NULL);
  style.setBorder("red");
  style.setBorderWidth("inherit");
  assertEquals(std::string(""), style.border());



  /**
   * errors
   */

  style.setBorder(NULL);
  style.setBorder("invalid");
  assert(style.border() != NULL);
  assertEquals(std::string(""), style.border());

  style.setBorder(NULL);
  style.setBorder("inherit inherit inherit");
  assert(style.border() != NULL);
  assertEquals(std::string(""), style.border());

  style.setBorder(NULL);
  style.setBorder("inherit dotted red");
  assert(style.border() != NULL);
  assertEquals(std::string(""), style.border());
}



void shorthand() {

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);


  style.setBorder(NULL);
  style.setBorder("red");
  style.setBorderTopWidth("thin");
  assert(style.border() != NULL);
  assertEquals(std::string(""), style.border());
}



void initial() {

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);


  style.setBorder(NULL);
  style.setBorder("dotted");
  assert(style.border() != NULL);
  assertEquals(std::string("rgb(0, 0, 0)"), style.borderColor());

  style.setColor(NULL);
  style.setColor("red");
  style.setBorder(NULL);
  style.setBorder("dotted");
  assertEquals(std::string("dotted red"), style.border());
  assertEquals(std::string("red"), style.borderColor());

  style.setColor(NULL);
  /* assertEquals(std::string("red"), style.borderColor()); */
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
  borderTopWidth();
  borderRightWidth();
  borderBottomWidth();
  borderLeftWidth();
  borderWidth();
  borderTop();
  borderRight();
  borderBottom();
  borderLeft();
  border();
  shorthand();
  initial();
}



} // test
