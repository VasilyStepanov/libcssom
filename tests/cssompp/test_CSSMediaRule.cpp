#include "test_CSSMediaRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void cssText() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::MEDIA_RULE);
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  /**
   * cssText()
   */

  // TODO:
  // cssText = "@media screen { p { color : green; } }";
  cssText = "@media { p { color : green; } }";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@media all {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"  div {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  // cssText = "@media all { p { color : green; } div { color : green; } }";
  cssText = "@media { p { color : green; } div { color : green; } }";
  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);
  assertEquals(cssText, cssRule.cssText());



  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void cssRules() {
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);

  assert(cssRule.cssRules().size() == 1);
  assert(cssRule.cssRules()[0].type() == cssom::CSSRule::STYLE_RULE);
}



} // unnamed

namespace test {



void cssMediaRule() {
  cssText();
  cssRules();
}



} // test
