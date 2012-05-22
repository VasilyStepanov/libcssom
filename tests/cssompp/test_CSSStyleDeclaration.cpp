#include "test_CSSStyleDeclaration.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleDeclarationValue.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void cssText() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "color : green; background-color : maroon;";
  assertEquals(cssText, style.cssText());



  /**
   * set cssText
   */

  cssText = "background-color : red; color : red;";
  style.setCSSText("background-color : red; color : red;");
  assertEquals(cssText, style.cssText());



  assert(errors.syntaxErrors == 0);
  cssText = "";
  style.setCSSText("invalid");
  assert(errors.syntaxErrors == 1);
  assertEquals(cssText, style.cssText());
}



void length() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  assert(style.length() == 2);
}



void item() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "color";
  assertEquals(cssText, style.item(0));

  cssText = "background-color";
  assertEquals(cssText, style.item(1));

  assert(style.item(2) == NULL);
}



void getPropertyValue() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "green";
  assertEquals(cssText, style.getPropertyValue("color"));

  cssText = "maroon";
  assertEquals(cssText, style.getPropertyValue("background-color"));

  assert(style.getPropertyValue("font-face") == NULL);

  assert(style.getPropertyValue("foo") == NULL);
}



void getPropertyPriority() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon !important;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "";
  assertEquals(cssText, style.getPropertyPriority("color"));

  cssText = "important";
  assertEquals(cssText, style.getPropertyPriority("background-color"));

  cssText = "";
  assertEquals(cssText, style.getPropertyPriority("font-face"));

  cssText = "";
  assertEquals(cssText, style.getPropertyPriority("foo"));
}



void setProperty() {
  std::string cssText;
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  /**
   * Test NULLs.
   */

  cssText = "color : green;";
  style.setProperty(NULL, NULL);
  assertEquals(cssText, style.cssText());

  style.setProperty("invalid", NULL);
  assertEquals(cssText, style.cssText());

  style.setProperty("background-color", NULL);
  assertEquals(cssText, style.cssText());

  cssText = "";
  style.setProperty("color", NULL);
  assertEquals(cssText, style.cssText());



  cssText = "color : red;";
  style.setProperty("color", "red");
  assertEquals(cssText, style.cssText());

  cssText = "color : red;";
  assert(errors.syntaxErrors == 0);
  style.setProperty("color", "& invalid");
  assertEquals(cssText, style.cssText());
  assert(errors.syntaxErrors == 1);

  cssText = "color : green;";
  style.setProperty("color", "green");
  assertEquals(cssText, style.cssText());

  cssText = "color : green; background-color : maroon;";
  style.setProperty("background-color", "maroon");
  assertEquals(cssText, style.cssText());

  cssText = "background-color : maroon; color : green;";
  style.setProperty("color", "green");
  assertEquals(cssText, style.cssText());



  /**
   * Test priority.
   */

  cssText = "background-color : maroon; color : red;";
  style.setProperty("color", "red", NULL);
  assertEquals(cssText, style.cssText());

  cssText = "background-color : maroon; color : maroon;";
  style.setProperty("color", "maroon", "");
  assertEquals(cssText, style.cssText());

  cssText = "background-color : maroon; color : green !important;";
  style.setProperty("color", "green", "!important");
  assertEquals(cssText, style.cssText());

  cssText = "background-color : maroon; color : green !important;";
  assert(errors.syntaxErrors == 1);
  style.setProperty("color", "red", "invalid");
  assertEquals(cssText, style.cssText());
  assert(errors.syntaxErrors == 2);

  cssText = "background-color : maroon; color : green;";
  style.setProperty("color", "green", "");
  assertEquals(cssText, style.cssText());
}




void setPropertyOrder() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "color : green; background-color : maroon;";
  assertEquals(cssText, style.cssText());



  cssText = "color : green; background-color : maroon;";
  style.setProperty("color", "& invalid");
  assertEquals(cssText, style.cssText());
}




void removeProperty() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" background-color : green;\n"
" color : green;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();



  cssText = "color : green;";
  assertEquals(std::string("green"),
    std::string(style.removeProperty("background-color")));
  assertEquals(cssText, style.cssText());

  cssText = "color : green;";
  assert(style.removeProperty("foo") == NULL);
  assertEquals(cssText, style.cssText());

  cssText = "color : green;";
  assert(style.removeProperty("font-face") == NULL);
  assertEquals(cssText, style.cssText());

  cssText = "";
  assertEquals(std::string("green"),
    std::string(style.removeProperty("color")));
  assertEquals(cssText, style.cssText());

  cssText = "";
  assert(style.removeProperty("color") == NULL);
  assertEquals(cssText, style.cssText());
}



void values() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();

  cssom::CSSStyleDeclarationValue values = style.values();

  assert(style.values().isNull() == false);
}



void parentRule() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
" color : green;\n"
" background-color : maroon;\n"
"}\n"
  );
  cssom::CSSStyleRule cssRule = cssom::CSSStyleRule::cast(
    styleSheet.cssRules()[0]);
  cssom::CSSStyleDeclaration style = cssRule.style();


  assert(style.parentRule() == cssRule);
}



cssom::CSSStyleDeclaration getStyleDeclaration(const cssom::CSSOM &cssom) {
  return cssom::CSSStyleRule::cast(cssom.parse("p {}").cssRules()[0]).style();
}



void azimuth() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.azimuth() == NULL);



  /**
   * angle
   */

  style.setAzimuth("180deg");
  assertEquals(std::string("180deg"), style.azimuth());

  style.setAzimuth("180.1deg");
  assertEquals(std::string("180.1deg"), style.azimuth());

  style.setAzimuth("-180DEG");
  assertEquals(std::string("180deg"), style.azimuth());

  style.setAzimuth("3.14rad");
  assertEquals(std::string("3.14rad"), style.azimuth());

  style.setAzimuth("-3.14RAD");
  assertEquals(std::string("3.14319rad"), style.azimuth());

  style.setAzimuth("200grad");
  assertEquals(std::string("200grad"), style.azimuth());

  style.setAzimuth("200.1grad");
  assertEquals(std::string("200.1grad"), style.azimuth());

  style.setAzimuth("-200GRAD");
  assertEquals(std::string("200grad"), style.azimuth());

  style.setAzimuth("-200GRAD");
  assertEquals(std::string("200grad"), style.azimuth());



  /**
   * left-side
   */

  style.setAzimuth("left-side");
  assertEquals(std::string("left-side"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("LEFT-SIDE");
  assertEquals(std::string("LEFT-SIDE"), style.azimuth());



  /**
   * left-side behind
   */

  style.setAzimuth("left-side behind");
  assertEquals(std::string("left-side behind"), style.azimuth());

  style.setAzimuth("behind left-side");
  assertEquals(std::string("behind left-side"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND LEFT-SIDE");
  assertEquals(std::string("BEHIND LEFT-SIDE"), style.azimuth());



  /**
   * far-left
   */

  style.setAzimuth("far-left");
  assertEquals(std::string("far-left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("FAR-LEFT");
  assertEquals(std::string("FAR-LEFT"), style.azimuth());



  /**
   * far-left behind
   */

  style.setAzimuth("far-left behind");
  assertEquals(std::string("far-left behind"), style.azimuth());

  style.setAzimuth("behind far-left");
  assertEquals(std::string("behind far-left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND FAR-LEFT");
  assertEquals(std::string("BEHIND FAR-LEFT"), style.azimuth());



  /**
   * left
   */

  style.setAzimuth("left");
  assertEquals(std::string("left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("LEFT");
  assertEquals(std::string("LEFT"), style.azimuth());



  /**
   * left behind
   */

  style.setAzimuth("left behind");
  assertEquals(std::string("left behind"), style.azimuth());

  style.setAzimuth("behind left");
  assertEquals(std::string("behind left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND LEFT");
  assertEquals(std::string("BEHIND LEFT"), style.azimuth());



  /**
   * center-left
   */

  style.setAzimuth("center-left");
  assertEquals(std::string("center-left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("CENTER-LEFT");
  assertEquals(std::string("CENTER-LEFT"), style.azimuth());



  /**
   * center-left behind
   */

  style.setAzimuth("center-left behind");
  assertEquals(std::string("center-left behind"), style.azimuth());

  style.setAzimuth("behind center-left");
  assertEquals(std::string("behind center-left"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND CENTER-LEFT");
  assertEquals(std::string("BEHIND CENTER-LEFT"), style.azimuth());



  /**
   * center
   */

  style.setAzimuth("center");
  assertEquals(std::string("center"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("CENTER");
  assertEquals(std::string("CENTER"), style.azimuth());



  /**
   * center behind
   */

  style.setAzimuth("center behind");
  assertEquals(std::string("center behind"), style.azimuth());

  style.setAzimuth("behind center");
  assertEquals(std::string("behind center"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND CENTER");
  assertEquals(std::string("BEHIND CENTER"), style.azimuth());



  /**
   * center-right
   */

  style.setAzimuth("center-right");
  assertEquals(std::string("center-right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("CENTER-RIGHT");
  assertEquals(std::string("CENTER-RIGHT"), style.azimuth());



  /**
   * center-right behind
   */

  style.setAzimuth("center-right behind");
  assertEquals(std::string("center-right behind"), style.azimuth());

  style.setAzimuth("behind center-right");
  assertEquals(std::string("behind center-right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND CENTER-RIGHT");
  assertEquals(std::string("BEHIND CENTER-RIGHT"), style.azimuth());



  /**
   * right
   */

  style.setAzimuth("right");
  assertEquals(std::string("right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("RIGHT");
  assertEquals(std::string("RIGHT"), style.azimuth());



  /**
   * right behind
   */

  style.setAzimuth("right behind");
  assertEquals(std::string("right behind"), style.azimuth());

  style.setAzimuth("behind right");
  assertEquals(std::string("behind right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND RIGHT");
  assertEquals(std::string("BEHIND RIGHT"), style.azimuth());



  /**
   * far-right
   */

  style.setAzimuth("far-right");
  assertEquals(std::string("far-right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("FAR-RIGHT");
  assertEquals(std::string("FAR-RIGHT"), style.azimuth());



  /**
   * far-right behind
   */

  style.setAzimuth("far-right behind");
  assertEquals(std::string("far-right behind"), style.azimuth());

  style.setAzimuth("behind far-right");
  assertEquals(std::string("behind far-right"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND FAR-RIGHT");
  assertEquals(std::string("BEHIND FAR-RIGHT"), style.azimuth());



  /**
   * right-side
   */

  style.setAzimuth("right-side");
  assertEquals(std::string("right-side"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("RIGHT-SIDE");
  assertEquals(std::string("RIGHT-SIDE"), style.azimuth());



  /**
   * right-side behind
   */

  style.setAzimuth("right-side behind");
  assertEquals(std::string("right-side behind"), style.azimuth());

  style.setAzimuth("behind right-side");
  assertEquals(std::string("behind right-side"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("BEHIND RIGHT-SIDE");
  assertEquals(std::string("BEHIND RIGHT-SIDE"), style.azimuth());



  /**
   * leftwards
   */

  style.setAzimuth("leftwards");
  assertEquals(std::string("leftwards"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("LEFTWARDS");
  assertEquals(std::string("LEFTWARDS"), style.azimuth());



  /**
   * rightwards
   */

  style.setAzimuth("rightwards");
  assertEquals(std::string("rightwards"), style.azimuth());

  /**
   * TODO: Replace with case insensitive implementation.
   */
  style.setAzimuth("RIGHTWARDS");
  assertEquals(std::string("RIGHTWARDS"), style.azimuth());



  /**
   * inherit
   */

  style.setAzimuth("inherit");
  assertEquals(std::string("inherit"), style.azimuth());

  style.setAzimuth("INHERIT");
  assertEquals(std::string("inherit"), style.azimuth());



  /**
   * errors
   */

  style.setAzimuth("invalid");
  assertEquals(std::string("inherit"), style.azimuth());

  style.setAzimuth("left-side behind inherit");
  assertEquals(std::string("inherit"), style.azimuth());

  style.setAzimuth("leftwards behind");
  assertEquals(std::string("inherit"), style.azimuth());
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



void cssStyleDeclaration() {
  cssText();
  length();
  item();
  getPropertyValue();
  getPropertyPriority();
  setProperty();
  setPropertyOrder();
  removeProperty();
  values();
  parentRule();
  azimuth();
  backgroundAttachment();
  backgroundColor();
  backgroundImage();
  backgroundPosition();
  backgroundRepeat();
}



} // test
