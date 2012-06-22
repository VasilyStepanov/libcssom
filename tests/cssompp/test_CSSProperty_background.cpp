#include "test_CSSProperty_background.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSPropertyValue.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleDeclarationValue.hpp>
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

  /**
   * scroll | fixed | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundAttachment() == NULL);



  /**
   * scroll
   */

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("scroll");
  assertEquals(std::string("scroll"), style.backgroundAttachment());

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("SCROLL");
  assertEquals(std::string("scroll"), style.backgroundAttachment());



  /**
   * fixed
   */

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("fixed");
  assertEquals(std::string("fixed"), style.backgroundAttachment());

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("FIXED");
  assertEquals(std::string("fixed"), style.backgroundAttachment());



  /**
   * inherit
   */

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("inherit");
  assertEquals(std::string("inherit"), style.backgroundAttachment());

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundAttachment());



  /**
   * errors
   */

  style.setBackgroundAttachment(NULL);
  style.setBackgroundAttachment("invalid");
  assert(style.backgroundAttachment() == NULL);
}



void backgroundColor() {
  
  /**
   * <color> | transparent | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundColor() == NULL);



  /**
   * color
   */

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("aqua");
  assertEquals(std::string("aqua"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("black");
  assertEquals(std::string("black"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("blue");
  assertEquals(std::string("blue"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("fuchsia");
  assertEquals(std::string("fuchsia"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("gray");
  assertEquals(std::string("gray"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("green");
  assertEquals(std::string("green"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("lime");
  assertEquals(std::string("lime"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("maroon");
  assertEquals(std::string("maroon"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("navy");
  assertEquals(std::string("navy"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("olive");
  assertEquals(std::string("olive"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("orange");
  assertEquals(std::string("orange"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("purple");
  assertEquals(std::string("purple"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("red");
  assertEquals(std::string("red"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("silver");
  assertEquals(std::string("silver"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("teal");
  assertEquals(std::string("teal"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("white");
  assertEquals(std::string("white"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("yellow");
  assertEquals(std::string("yellow"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("YELLOW");
  assertEquals(std::string("yellow"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("#f00");
  assertEquals(std::string("rgb(255, 0, 0)"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("#00ff00");
  assertEquals(std::string("rgb(0, 255, 0)"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("rgb(0, 0, 255)");
  assertEquals(std::string("rgb(0, 0, 255)"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("RGB(0, 0, 255)");
  assertEquals(std::string("rgb(0, 0, 255)"), style.backgroundColor());



  /**
   * transparent
   */

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("transparent");
  assertEquals(std::string("transparent"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("TRANSPARENT");
  assertEquals(std::string("transparent"), style.backgroundColor());



  /**
   * inherit
   */

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("inherit");
  assertEquals(std::string("inherit"), style.backgroundColor());

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundColor());



  /**
   * errors
   */

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("invalid");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("#00");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("#0000");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("#00ff000");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("rgb(0, 0, -1)");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("rgb(0, 0, 256)");
  assert(style.backgroundColor() == NULL);

  style.setBackgroundColor(NULL);
  style.setBackgroundColor("rgb(0, 0, 0, 0)");
  assert(style.backgroundColor() == NULL);
}



void backgroundImage() {

  /**
   * <uri> | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundImage() == NULL);


  
  /**
   * uri
   */

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("url(\"http://example.com/\")");
  assertEquals(std::string("url(\"http://example.com/\")"),
    style.backgroundImage());

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("url('http://example.com/')");
  assertEquals(std::string("url(\"http://example.com/\")"),
    style.backgroundImage());

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("URL(\"HTTP://EXAMPLE.COM/\")");
  assertEquals(std::string("url(\"HTTP://EXAMPLE.COM/\")"),
    style.backgroundImage());



  /**
   * none
   */

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("none");
  assertEquals(std::string("none"), style.backgroundImage());

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("NONE");
  assertEquals(std::string("none"), style.backgroundImage());



  /**
   * inherit
   */

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("inherit");
  assertEquals(std::string("inherit"), style.backgroundImage());

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundImage());



  /**
   * errors
   */

  style.setBackgroundImage(NULL);
  style.setBackgroundImage("invalid");
  assert(style.backgroundImage() == NULL);

}



void backgroundPosition() {
  
  /**
   * [ [ <percentage> | <length> | left | center | right ] [ <percentage> |
   *  <length> | top | center | bottom ]? ] | [ [ left | center | right ] ||
   *  [ top | center | bottom ] ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundPosition() == NULL);



  /**
   * [ <percentage> | <length> | left | center | right ]
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50%");
  assertEquals(std::string("50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px");
  assertEquals(std::string("50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left");
  assertEquals(std::string("left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT");
  assertEquals(std::string("left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center");
  assertEquals(std::string("center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER");
  assertEquals(std::string("center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right");
  assertEquals(std::string("right"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT");
  assertEquals(std::string("right"), style.backgroundPosition());



  /**
   * [ top | center | bottom ]
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("top");
  assertEquals(std::string("top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("bottom");
  assertEquals(std::string("bottom"), style.backgroundPosition());



  /**
   *  <percentage> | <length> | left | center | right ] <percentage>
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50% 50%");
  assertEquals(std::string("50% 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px 50%");
  assertEquals(std::string("50px 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left 50%");
  assertEquals(std::string("left 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT 50%");
  assertEquals(std::string("left 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center 50%");
  assertEquals(std::string("center 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER 50%");
  assertEquals(std::string("center 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right 50%");
  assertEquals(std::string("right 50%"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT 50%");
  assertEquals(std::string("right 50%"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] <length>
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50% 50px");
  assertEquals(std::string("50% 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px 50px");
  assertEquals(std::string("50px 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left 50px");
  assertEquals(std::string("left 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT 50px");
  assertEquals(std::string("left 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center 50px");
  assertEquals(std::string("center 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER 50px");
  assertEquals(std::string("center 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right 50px");
  assertEquals(std::string("right 50px"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT 50px");
  assertEquals(std::string("right 50px"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] top
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50% top");
  assertEquals(std::string("50% top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px top");
  assertEquals(std::string("50px top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left top");
  assertEquals(std::string("left top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT TOP");
  assertEquals(std::string("left top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center top");
  assertEquals(std::string("center top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER TOP");
  assertEquals(std::string("center top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right top");
  assertEquals(std::string("right top"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT TOP");
  assertEquals(std::string("right top"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] center
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50% center");
  assertEquals(std::string("50% center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px center");
  assertEquals(std::string("50px center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left center");
  assertEquals(std::string("left center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT CENTER");
  assertEquals(std::string("left center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center center");
  assertEquals(std::string("center center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER CENTER");
  assertEquals(std::string("center center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right center");
  assertEquals(std::string("right center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT CENTER");
  assertEquals(std::string("right center"), style.backgroundPosition());



  /**
   * [ <percentage> | <length> | left | center | right ] bottom
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50% bottom");
  assertEquals(std::string("50% bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px bottom");
  assertEquals(std::string("50px bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("left bottom");
  assertEquals(std::string("left bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("LEFT BOTTOM");
  assertEquals(std::string("left bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center center");
  assertEquals(std::string("center center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER BOTTOM");
  assertEquals(std::string("center bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("right bottom");
  assertEquals(std::string("right bottom"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("RIGHT BOTTOM");
  assertEquals(std::string("right bottom"), style.backgroundPosition());



  /**
   * [ left | center | right ] || [ top | center | bottom ]
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("top left");
  assertEquals(std::string("top left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("top center");
  assertEquals(std::string("top center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("top right");
  assertEquals(std::string("top right"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("TOP LEFT");
  assertEquals(std::string("top left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center left");
  assertEquals(std::string("center left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("center right");
  assertEquals(std::string("center right"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("CENTER LEFT");
  assertEquals(std::string("center left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("bottom left");
  assertEquals(std::string("bottom left"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("bottom center");
  assertEquals(std::string("bottom center"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("bottom right");
  assertEquals(std::string("bottom right"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("BOTTOM LEFT");
  assertEquals(std::string("bottom left"), style.backgroundPosition());



  /**
   * inherit
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("inherit");
  assertEquals(std::string("inherit"), style.backgroundPosition());

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundPosition());



  /**
   * errors
   */

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("invalid");
  assert(style.backgroundPosition() == NULL);

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("50px left");
  assert(style.backgroundPosition() == NULL);

  style.setBackgroundPosition(NULL);
  style.setBackgroundPosition("top 50px");
  assert(style.backgroundPosition() == NULL);
}



void backgroundRepeat() {

  /**
   * repeat | repeat-x | repeat-y | no-repeat | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.backgroundRepeat() == NULL);



  /**
   * repeat
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("repeat");
  assertEquals(std::string("repeat"), style.backgroundRepeat());

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("REPEAT");
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * repeat-x
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("repeat-x");
  assertEquals(std::string("repeat-x"), style.backgroundRepeat());

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("REPEAT-X");
  assertEquals(std::string("repeat-x"), style.backgroundRepeat());



  /**
   * repeat-y
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("repeat-y");
  assertEquals(std::string("repeat-y"), style.backgroundRepeat());

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("REPEAT-Y");
  assertEquals(std::string("repeat-y"), style.backgroundRepeat());



  /**
   * no-repeat
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("no-repeat");
  assertEquals(std::string("no-repeat"), style.backgroundRepeat());

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("NO-REPEAT");
  assertEquals(std::string("no-repeat"), style.backgroundRepeat());



  /**
   * inherit
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("inherit");
  assertEquals(std::string("inherit"), style.backgroundRepeat());

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("INHERIT");
  assertEquals(std::string("inherit"), style.backgroundRepeat());



  /**
   * errors
   */

  style.setBackgroundRepeat(NULL);
  style.setBackgroundRepeat("invalid");
  assert(style.backgroundRepeat() == NULL);

}



void background() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.background() == NULL);



  /**
   * color
   */

  style.setBackground(NULL);
  style.setBackground("#808080");
  assertEquals(std::string("rgb(128, 128, 128)"), style.background());
  assertEquals(std::string("scroll"), style.backgroundAttachment());
  assertEquals(std::string("rgb(128, 128, 128)"), style.backgroundColor());
  assertEquals(std::string("none"), style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * image
   */

  style.setBackground(NULL);
  style.setBackground("url(\"http://example.com/\")");
  assertEquals(std::string("url(\"http://example.com/\")"), style.background());
  assertEquals(std::string("scroll"), style.backgroundAttachment());
  assertEquals(std::string("transparent"), style.backgroundColor());
  assertEquals(std::string("url(\"http://example.com/\")"),
    style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * repeat
   */

  style.setBackground(NULL);
  style.setBackground("repeat-x");
  assertEquals(std::string("repeat-x"), style.background());
  assertEquals(std::string("scroll"), style.backgroundAttachment());
  assertEquals(std::string("transparent"), style.backgroundColor());
  assertEquals(std::string("none"), style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("repeat-x"), style.backgroundRepeat());



  /**
   * attachment
   */

  style.setBackground(NULL);
  style.setBackground("fixed");
  assertEquals(std::string("fixed"), style.background());
  assertEquals(std::string("fixed"), style.backgroundAttachment());
  assertEquals(std::string("transparent"), style.backgroundColor());
  assertEquals(std::string("none"), style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * position
   */

  style.setBackground(NULL);
  style.setBackground("center center");
  assertEquals(std::string("center center"), style.background());
  assertEquals(std::string("scroll"), style.backgroundAttachment());
  assertEquals(std::string("transparent"), style.backgroundColor());
  assertEquals(std::string("none"), style.backgroundImage());
  assertEquals(std::string("center center"), style.backgroundPosition());
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * repeat attachment
   */

  style.setBackground(NULL);
  style.setBackground("fixed no-repeat");
  assertEquals(std::string("no-repeat fixed"), style.background());
  assertEquals(std::string("fixed"), style.backgroundAttachment());
  assertEquals(std::string("transparent"), style.backgroundColor());
  assertEquals(std::string("none"), style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("no-repeat"), style.backgroundRepeat());



  /**
   * color image
   */

  style.setBackground(NULL);
  style.setBackground("inherit #808080");
  assertEquals(std::string("rgb(128, 128, 128) inherit"), style.background());
  assertEquals(std::string("scroll"), style.backgroundAttachment());
  assertEquals(std::string("rgb(128, 128, 128)"), style.backgroundColor());
  assertEquals(std::string("inherit"), style.backgroundImage());
  assertEquals(std::string("0% 0%"), style.backgroundPosition());
  assertEquals(std::string("repeat"), style.backgroundRepeat());



  /**
   * inherit
   */

  style.setBackground(NULL);
  style.setBackground("inherit");
  assertEquals(std::string("inherit"), style.background());
  assertEquals(std::string("inherit"), style.backgroundAttachment());
  assertEquals(std::string("inherit"), style.backgroundColor());
  assertEquals(std::string("inherit"), style.backgroundImage());
  assertEquals(std::string("inherit"), style.backgroundPosition());
  assertEquals(std::string("inherit"), style.backgroundRepeat());



  /**
   * omit initial
   */

  style.setBackground(NULL);

  /**
   * TODO: Drop next five lines.
   */
  style.setBackground("inherit");
  style.setBackgroundAttachment(NULL);
  style.setBackgroundColor(NULL);
  style.setBackgroundImage(NULL);
  style.setBackgroundPosition(NULL);
  style.setBackgroundRepeat(NULL);

  style.setBackgroundAttachment("fixed");
  assertEquals(std::string(""), style.background());
  style.setBackgroundColor("transparent");
  style.setBackgroundImage("none");
  style.setBackgroundPosition("0% 0%");
  style.setBackgroundRepeat("repeat");
  assertEquals(std::string("fixed"), style.background());

  style.setBackgroundAttachment("scroll");
  assertEquals(std::string("transparent"), style.background());



  /**
   * imposible shorthand
   */

  style.setBackground(NULL);
  style.setBackground("inherit");
  style.setBackgroundImage(NULL);
  assertEquals(std::string(""), style.background());



  /**
   * error
   */

  style.setBackground(NULL);
  style.setBackground("invalid");
  assert(style.background() == NULL);

}



void shorthand() {
  cssom::CSSOM cssom;
  cssom::CSSPropertyValue background;
  cssom::CSSPropertyValue backgroundColor;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.background() == NULL);



  /**
   * remove shorthand
   */

  style.setBackground(NULL);
  assert(style.length() == 0);
  style.setBackground("red");
  backgroundColor = style.values().getProperty("background-color");
  assert(style.length() == 6);
  assertEquals(std::string(
"background : red; "
"background-color : red; "
"background-image : none; "
"background-repeat : repeat; "
"background-attachment : scroll; "
"background-position : 0% 0%;"),
    style.cssText());
  style.setBackground(NULL);
  std::cout << backgroundColor.cssText() << std::endl;
  assert(style.length() == 0);

}



} // unnamed

namespace test {



void cssPropertyBackground() {
  backgroundAttachment();
  backgroundColor();
  backgroundImage();
  backgroundPosition();
  backgroundRepeat();
  background();
  shorthand();
}



} // test
