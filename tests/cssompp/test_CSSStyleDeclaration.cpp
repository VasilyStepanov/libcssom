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


  assert(style.azimuth() == NULL);

  style.setBackgroundAttachment("center");
  assertEquals(std::string("center"), style.backgroundAttachment());
}



void backgroundColor() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);


  assert(style.azimuth() == NULL);

  style.setBackgroundColor("center");
  assertEquals(std::string("center"), style.backgroundColor());
}



void backgroundImage() {
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);


  assert(style.azimuth() == NULL);

  style.setBackgroundImage("center");
  assertEquals(std::string("center"), style.backgroundImage());
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
