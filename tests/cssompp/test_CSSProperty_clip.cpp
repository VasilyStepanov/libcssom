#include "test_CSSProperty_clip.hpp"

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



void clip() {
  
  /**
   * <shape> | auto | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.clip() == NULL);



  /**
   * <shape>
   */

  style.setClip(NULL);
  style.setClip("rect(1px, 1px, 1px, 1px)");
  assertEquals(std::string("rect(1px, 1px, 1px, 1px)"), style.clip());

  style.setClip(NULL);
  style.setClip("rect(1px, auto, 1px, 1px)");
  assertEquals(std::string("rect(1px, auto, 1px, 1px)"), style.clip());

  style.setClip(NULL);
  style.setClip("rect(1px, auto, AUTO, 1px)");
  assertEquals(std::string("rect(1px, auto, auto, 1px)"), style.clip());



  /**
   * auto
   */

  style.setClip(NULL);
  style.setClip("auto");
  assertEquals(std::string("auto"), style.clip());

  style.setClip(NULL);
  style.setClip("AUTO");
  assertEquals(std::string("auto"), style.clip());



  /**
   * inherit
   */

  style.setClip(NULL);
  style.setClip("inherit");
  assertEquals(std::string("inherit"), style.clip());

  style.setClip(NULL);
  style.setClip("INHERIT");
  assertEquals(std::string("inherit"), style.clip());



  /**
   * errors
   */

  style.setClip(NULL);
  style.setClip("invalid");
  assert(style.clip() == NULL);

  style.setClip(NULL);
  style.setClip("rect(1px, 1px, 1px)");
  assert(style.clip() == NULL);

  style.setClip(NULL);
  style.setClip("rect(1px, 1px, 1px, 1px, 1px)");
  assert(style.clip() == NULL);
}



} // unnamed

namespace test {



void cssPropertyClip() {
  clip();
}



} // test
