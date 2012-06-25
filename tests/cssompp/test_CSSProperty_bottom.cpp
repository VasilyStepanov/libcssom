#include "test_CSSProperty_bottom.hpp"

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



void bottom() {
  
  /**
   * <length> | <percentage> | auto | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.bottom() == NULL);



  /**
   * <length>
   */

  style.setBottom(NULL);
  style.setBottom("1px");
  assertEquals(std::string("1px"), style.bottom());



  /**
   * <percentage>
   */

  style.setBottom(NULL);
  style.setBottom("1%");
  assertEquals(std::string("1%"), style.bottom());



  /**
   * auto
   */

  style.setBottom(NULL);
  style.setBottom("auto");
  assertEquals(std::string("auto"), style.bottom());

  style.setBottom(NULL);
  style.setBottom("AUTO");
  assertEquals(std::string("auto"), style.bottom());



  /**
   * inherit
   */

  style.setBottom(NULL);
  style.setBottom("inherit");
  assertEquals(std::string("inherit"), style.bottom());

  style.setBottom(NULL);
  style.setBottom("INHERIT");
  assertEquals(std::string("inherit"), style.bottom());



  /**
   * errors
   */

  style.setBottom(NULL);
  style.setBottom("invalid");
  assert(style.bottom() == NULL);

  style.setBottom(NULL);
  style.setBottom("0");
  assertEquals(std::string("0"), style.bottom());

  style.setBottom(NULL);
  style.setBottom("1");
  assert(style.bottom() == NULL);
}



} // unnamed

namespace test {



void cssPropertyBottom() {
  bottom();
}



} // test
