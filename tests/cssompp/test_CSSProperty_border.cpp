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



} // unnamed

namespace test {



void cssPropertyBorder() {
  borderCollapse();
  borderSpacing();
}



} // test
