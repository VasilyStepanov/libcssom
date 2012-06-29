#include "test_CSSProperty_captionSide.hpp"

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



void captionSide() {
  
  /**
   * top | bottom | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.captionSide() == NULL);



  /**
   * top
   */

  style.setCaptionSide(NULL);
  style.setCaptionSide("top");
  assertEquals(std::string("top"), style.captionSide());

  style.setCaptionSide(NULL);
  style.setCaptionSide("TOP");
  assertEquals(std::string("top"), style.captionSide());



  /**
   * bottom
   */

  style.setCaptionSide(NULL);
  style.setCaptionSide("bottom");
  assertEquals(std::string("bottom"), style.captionSide());

  style.setCaptionSide(NULL);
  style.setCaptionSide("BOTTOM");
  assertEquals(std::string("bottom"), style.captionSide());



  /**
   * inherit
   */

  style.setCaptionSide(NULL);
  style.setCaptionSide("inherit");
  assertEquals(std::string("inherit"), style.captionSide());

  style.setCaptionSide(NULL);
  style.setCaptionSide("INHERIT");
  assertEquals(std::string("inherit"), style.captionSide());



  /**
   * errors
   */

  style.setCaptionSide(NULL);
  style.setCaptionSide("invalid");
  assert(style.captionSide() == NULL);
}



} // unnamed

namespace test {



void cssPropertyCaptionSide() {
  captionSide();
}



} // test
