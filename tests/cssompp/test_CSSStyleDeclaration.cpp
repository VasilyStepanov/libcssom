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

  style.setAzimuth("center");
  assertEquals(std::string("center"), style.azimuth());



  style.setAzimuth(NULL);
  assert(style.azimuth() == NULL);
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


  assert(style.azimuth() == NULL);

  style.setBackgroundPosition("center");
  assertEquals(std::string("center"), style.backgroundPosition());
}



void backgroundRepeat() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);


  assert(style.azimuth() == NULL);

  style.setBackgroundRepeat("center");
  assertEquals(std::string("center"), style.backgroundRepeat());
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
