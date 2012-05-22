#include "test_CSSProperty_background.hpp"

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



void backgroundAttachment() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundAttachment() == NULL);



  /**
   * scroll
   */

  style.setBackgroundAttachment("scroll");
  assertEquals(std::string("scroll"), style.backgroundAttachment());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundAttachment("SCROLL");
  assertEquals(std::string("SCROLL"), style.backgroundAttachment());



  /**
   * fixed
   */

  style.setBackgroundAttachment("fixed");
  assertEquals(std::string("fixed"), style.backgroundAttachment());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundAttachment("FIXED");
  assertEquals(std::string("FIXED"), style.backgroundAttachment());



  /**
   * inherit
   */

  style.setBackgroundAttachment("inherit");
  assertEquals(std::string("inherit"), style.backgroundAttachment());

  style.setBackgroundAttachment("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundAttachment());



  /**
   * errors
   */

  style.setBackgroundAttachment("invalid");
  assertEquals(std::string("inherit"), style.backgroundAttachment());
}



void backgroundColor() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundColor() == NULL);



  /**
   * color
   */

  style.setBackgroundColor("aqua");
  assertEquals(std::string("aqua"), style.backgroundColor());

  style.setBackgroundColor("black");
  assertEquals(std::string("black"), style.backgroundColor());

  style.setBackgroundColor("blue");
  assertEquals(std::string("blue"), style.backgroundColor());

  style.setBackgroundColor("fuchsia");
  assertEquals(std::string("fuchsia"), style.backgroundColor());

  style.setBackgroundColor("gray");
  assertEquals(std::string("gray"), style.backgroundColor());

  style.setBackgroundColor("green");
  assertEquals(std::string("green"), style.backgroundColor());

  style.setBackgroundColor("lime");
  assertEquals(std::string("lime"), style.backgroundColor());

  style.setBackgroundColor("maroon");
  assertEquals(std::string("maroon"), style.backgroundColor());

  style.setBackgroundColor("navy");
  assertEquals(std::string("navy"), style.backgroundColor());

  style.setBackgroundColor("olive");
  assertEquals(std::string("olive"), style.backgroundColor());

  style.setBackgroundColor("orange");
  assertEquals(std::string("orange"), style.backgroundColor());

  style.setBackgroundColor("purple");
  assertEquals(std::string("purple"), style.backgroundColor());

  style.setBackgroundColor("red");
  assertEquals(std::string("red"), style.backgroundColor());

  style.setBackgroundColor("silver");
  assertEquals(std::string("silver"), style.backgroundColor());

  style.setBackgroundColor("teal");
  assertEquals(std::string("teal"), style.backgroundColor());

  style.setBackgroundColor("white");
  assertEquals(std::string("white"), style.backgroundColor());

  style.setBackgroundColor("yellow");
  assertEquals(std::string("yellow"), style.backgroundColor());

  /**
   * TODO: Replace with case insensitive implementation.
   */

  style.setBackgroundColor("YELLOW");
  assertEquals(std::string("YELLOW"), style.backgroundColor());

  style.setBackgroundColor("#f00");
  assertEquals(std::string("rgb(255, 0, 0)"), style.backgroundColor());

  style.setBackgroundColor("#00ff00");
  assertEquals(std::string("rgb(0, 255, 0)"), style.backgroundColor());

  style.setBackgroundColor("rgb(0, 0, 255)");
  assertEquals(std::string("rgb(0, 0, 255)"), style.backgroundColor());

  style.setBackgroundColor("RGB(0, 0, 255)");
  assertEquals(std::string("rgb(0, 0, 255)"), style.backgroundColor());



  /**
   * transparent
   */

  style.setBackgroundColor("transparent");
  assertEquals(std::string("transparent"), style.backgroundColor());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundColor("TRANSPARENT");
  assertEquals(std::string("TRANSPARENT"), style.backgroundColor());



  /**
   * inherit
   */

  style.setBackgroundColor("inherit");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundColor());



  /**
   * errors
   */

  style.setBackgroundColor("invalid");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("#00");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("#0000");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("#00ff000");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("rgb(0, 0, -1)");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("rgb(0, 0, 256)");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor("rgb(0, 0, 0, 0)");
  assertEquals(std::string("inherit"), style.backgroundColor());
}



void backgroundImage() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundImage() == NULL);


  
  /**
   * uri
   */

  style.setBackgroundImage("url(\"http://example.com/\")");
  assertEquals(std::string("url(\"http://example.com/\")"),
    style.backgroundImage());

  style.setBackgroundImage("url('http://example.com/')");
  assertEquals(std::string("url(\"http://example.com/\")"),
    style.backgroundImage());

  style.setBackgroundImage("URL(\"HTTP://EXAMPLE.COM/\")");
  assertEquals(std::string("url(\"HTTP://EXAMPLE.COM/\")"),
    style.backgroundImage());



  /**
   * none
   */

  style.setBackgroundImage("none");
  assertEquals(std::string("none"), style.backgroundImage());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundImage("NONE");
  assertEquals(std::string("NONE"), style.backgroundImage());



  /**
   * inherit
   */

  style.setBackgroundImage("inherit");
  assertEquals(std::string("inherit"), style.backgroundImage());

  style.setBackgroundImage("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundImage());



  /**
   * errors
   */

  style.setBackgroundImage("invalid");
  assertEquals(std::string("inherit"), style.backgroundImage());

}



void backgroundPosition() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundPosition() == NULL);



  /**
   * [ <percentage> | <length> | left | center | right ]
   */

  style.setBackgroundPosition("50%");
  assertEquals(std::string("50%"), style.backgroundPosition());

  style.setBackgroundPosition("50px");
  assertEquals(std::string("50px"), style.backgroundPosition());

  style.setBackgroundPosition("left");
  assertEquals(std::string("left"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT");
  assertEquals(std::string("LEFT"), style.backgroundPosition());

  style.setBackgroundPosition("center");
  assertEquals(std::string("center"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER");
  assertEquals(std::string("CENTER"), style.backgroundPosition());

  style.setBackgroundPosition("right");
  assertEquals(std::string("right"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT");
  assertEquals(std::string("RIGHT"), style.backgroundPosition());



  /**
   * [ top | center | bottom ]
   */

  style.setBackgroundPosition("top");
  assertEquals(std::string("top"), style.backgroundPosition());

  style.setBackgroundPosition("bottom");
  assertEquals(std::string("bottom"), style.backgroundPosition());



  /**
   *  <percentage> | <length> | left | center | right ] <percentage>
   */

  style.setBackgroundPosition("50% 50%");
  assertEquals(std::string("50% 50%"), style.backgroundPosition());

  style.setBackgroundPosition("50px 50%");
  assertEquals(std::string("50px 50%"), style.backgroundPosition());

  style.setBackgroundPosition("left 50%");
  assertEquals(std::string("left 50%"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT 50%");
  assertEquals(std::string("LEFT 50%"), style.backgroundPosition());

  style.setBackgroundPosition("center 50%");
  assertEquals(std::string("center 50%"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER 50%");
  assertEquals(std::string("CENTER 50%"), style.backgroundPosition());

  style.setBackgroundPosition("right 50%");
  assertEquals(std::string("right 50%"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT 50%");
  assertEquals(std::string("RIGHT 50%"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] <length>
   */

  style.setBackgroundPosition("50% 50px");
  assertEquals(std::string("50% 50px"), style.backgroundPosition());

  style.setBackgroundPosition("50px 50px");
  assertEquals(std::string("50px 50px"), style.backgroundPosition());

  style.setBackgroundPosition("left 50px");
  assertEquals(std::string("left 50px"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT 50px");
  assertEquals(std::string("LEFT 50px"), style.backgroundPosition());

  style.setBackgroundPosition("center 50px");
  assertEquals(std::string("center 50px"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER 50px");
  assertEquals(std::string("CENTER 50px"), style.backgroundPosition());

  style.setBackgroundPosition("right 50px");
  assertEquals(std::string("right 50px"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT 50px");
  assertEquals(std::string("RIGHT 50px"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] top
   */

  style.setBackgroundPosition("50% top");
  assertEquals(std::string("50% top"), style.backgroundPosition());

  style.setBackgroundPosition("50px top");
  assertEquals(std::string("50px top"), style.backgroundPosition());

  style.setBackgroundPosition("left top");
  assertEquals(std::string("left top"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT TOP");
  assertEquals(std::string("LEFT TOP"), style.backgroundPosition());

  style.setBackgroundPosition("center top");
  assertEquals(std::string("center top"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER TOP");
  assertEquals(std::string("CENTER TOP"), style.backgroundPosition());

  style.setBackgroundPosition("right top");
  assertEquals(std::string("right top"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT TOP");
  assertEquals(std::string("RIGHT TOP"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] center
   */

  style.setBackgroundPosition("50% center");
  assertEquals(std::string("50% center"), style.backgroundPosition());

  style.setBackgroundPosition("50px center");
  assertEquals(std::string("50px center"), style.backgroundPosition());

  style.setBackgroundPosition("left center");
  assertEquals(std::string("left center"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT CENTER");
  assertEquals(std::string("LEFT CENTER"), style.backgroundPosition());

  style.setBackgroundPosition("center center");
  assertEquals(std::string("center center"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER CENTER");
  assertEquals(std::string("CENTER CENTER"), style.backgroundPosition());

  style.setBackgroundPosition("right center");
  assertEquals(std::string("right center"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT CENTER");
  assertEquals(std::string("RIGHT CENTER"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] bottom
   */

  style.setBackgroundPosition("50% bottom");
  assertEquals(std::string("50% bottom"), style.backgroundPosition());

  style.setBackgroundPosition("50px bottom");
  assertEquals(std::string("50px bottom"), style.backgroundPosition());

  style.setBackgroundPosition("left bottom");
  assertEquals(std::string("left bottom"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("LEFT BOTTOM");
  assertEquals(std::string("LEFT BOTTOM"), style.backgroundPosition());

  style.setBackgroundPosition("center center");
  assertEquals(std::string("center center"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("CENTER BOTTOM");
  assertEquals(std::string("CENTER BOTTOM"), style.backgroundPosition());

  style.setBackgroundPosition("right bottom");
  assertEquals(std::string("right bottom"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundPosition("RIGHT BOTTOM");
  assertEquals(std::string("RIGHT BOTTOM"), style.backgroundPosition());



  /**
   * [ left | center | right ] || [ top | center | bottom ]
   */

  style.setBackgroundPosition("top left");
  assertEquals(std::string("top left"), style.backgroundPosition());

  style.setBackgroundPosition("top center");
  assertEquals(std::string("top center"), style.backgroundPosition());

  style.setBackgroundPosition("top right");
  assertEquals(std::string("top right"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */

  style.setBackgroundPosition("TOP LEFT");
  assertEquals(std::string("TOP LEFT"), style.backgroundPosition());

  style.setBackgroundPosition("center left");
  assertEquals(std::string("center left"), style.backgroundPosition());

  style.setBackgroundPosition("center right");
  assertEquals(std::string("center right"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */

  style.setBackgroundPosition("CENTER LEFT");
  assertEquals(std::string("CENTER LEFT"), style.backgroundPosition());

  style.setBackgroundPosition("bottom left");
  assertEquals(std::string("bottom left"), style.backgroundPosition());

  style.setBackgroundPosition("bottom center");
  assertEquals(std::string("bottom center"), style.backgroundPosition());

  style.setBackgroundPosition("bottom right");
  assertEquals(std::string("bottom right"), style.backgroundPosition());

  /**
   * TODO: Replace with case insensitive implementation.
   */

  style.setBackgroundPosition("BOTTOM LEFT");
  assertEquals(std::string("BOTTOM LEFT"), style.backgroundPosition());



  /**
   * inherit
   */

  style.setBackgroundPosition("inherit");
  assertEquals(std::string("inherit"), style.backgroundPosition());

  style.setBackgroundPosition("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundPosition());



  /**
   * errors
   */

  style.setBackgroundPosition("invalid");
  assertEquals(std::string("inherit"), style.backgroundPosition());

  style.setBackgroundPosition("50px left");
  assertEquals(std::string("inherit"), style.backgroundPosition());

  style.setBackgroundPosition("top 50px");
  assertEquals(std::string("inherit"), style.backgroundPosition());
}



void backgroundRepeat() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundRepeat() == NULL);



  /**
   * repeat
   */

  style.setBackgroundRepeat("repeat");
  assertEquals(std::string("repeat"), style.backgroundRepeat());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundRepeat("REPEAT");
  assertEquals(std::string("REPEAT"), style.backgroundRepeat());



  /**
   * repeat-x
   */

  style.setBackgroundRepeat("repeat-x");
  assertEquals(std::string("repeat-x"), style.backgroundRepeat());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundRepeat("REPEAT-X");
  assertEquals(std::string("REPEAT-X"), style.backgroundRepeat());



  /**
   * repeat-y
   */

  style.setBackgroundRepeat("repeat-y");
  assertEquals(std::string("repeat-y"), style.backgroundRepeat());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundRepeat("REPEAT-Y");
  assertEquals(std::string("REPEAT-Y"), style.backgroundRepeat());



  /**
   * no-repeat
   */

  style.setBackgroundRepeat("no-repeat");
  assertEquals(std::string("no-repeat"), style.backgroundRepeat());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setBackgroundRepeat("NO-REPEAT");
  assertEquals(std::string("NO-REPEAT"), style.backgroundRepeat());



  /**
   * inherit
   */

  style.setBackgroundRepeat("inherit");
  assertEquals(std::string("inherit"), style.backgroundRepeat());

  style.setBackgroundRepeat("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundRepeat());



  /**
   * errors
   */

  style.setBackgroundRepeat("invalid");
  assertEquals(std::string("inherit"), style.backgroundRepeat());

}



} // unnamed

namespace test {



void cssPropertyBackground() {
  backgroundAttachment();
  backgroundColor();
  backgroundImage();
  backgroundPosition();
  backgroundRepeat();
}



} // test
