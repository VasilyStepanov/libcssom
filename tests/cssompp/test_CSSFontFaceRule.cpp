#include "test_CSSFontFaceRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSFontFaceRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>

#include <assert.h>

namespace {



void cssText() {
  test::Errors errors;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(&test::errorHandler);
  std::string cssText;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@font-face {\n"
"  font-family: Gentium;\n"
"  src: url(http://example.com/fonts/Gentium.ttf);\n"
"}\n"
  );

  assert(styleSheet.cssRules().length() == 1);
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::FONT_FACE_RULE);

  cssom::CSSFontFaceRule cssRule = cssom::CSSFontFaceRule::cast(
    styleSheet.cssRules()[0]);



  /**
   * cssText()
   */

  cssText =
"@font-face { "
  "font-family : gentium; "
  "src : url(\"http://example.com/fonts/Gentium.ttf\"); "
"}";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@font-face {\n"
"  font-family: Foo;\n"
"  src: url(http://example.com/fonts/Foo.ttf);\n"
"}\n"
  );
  cssText =
"@font-face { "
  "font-family : foo; "
  "src : url(\"http://example.com/fonts/Foo.ttf\"); "
"}";
  assert(cssRule.type() == cssom::CSSRule::FONT_FACE_RULE);
  assertEquals(cssText, cssRule.cssText());



  assert(errors.invalidModificationErrors == 0);
  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(errors.invalidModificationErrors == 1);
  assert(cssRule.type() == cssom::CSSRule::FONT_FACE_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void style() {
  cssom::CSSOM cssom;
  std::string cssText;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@font-face {\n"
"  font-family: Gentium;\n"
"  src: url(http://example.com/fonts/Gentium.ttf);\n"
"}\n"
  );

  cssom::CSSFontFaceRule cssRule = cssom::CSSFontFaceRule::cast(
    styleSheet.cssRules()[0]);

  assert(cssRule.style().length() == 2);
}



} // unnamed

namespace test {



void cssFontFaceRule() {
  cssText();
  style();
}



} // test
