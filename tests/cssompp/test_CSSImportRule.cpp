#include "test_CSSImportRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSImportRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/MediaList.hpp>

#include <iostream>

#include <assert.h>

namespace {



void cssText() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(&test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@import url(\"bluish.css\") projection, tv;"
  );
  assert(styleSheet.cssRules().length() == 1);
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::IMPORT_RULE);
  cssom::CSSImportRule cssRule = cssom::CSSImportRule::cast(
    styleSheet.cssRules()[0]);

  /**
   * cssText()
   */

  cssText = "@import url('bluish.css') projection, tv;";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@import url('foo') bar;"
  );
  cssText = "@import url('foo') bar;";
  assert(cssRule.type() == cssom::CSSRule::IMPORT_RULE);
  assertEquals(cssText, cssRule.cssText());



  assert(errors.invalidModificationErrors == 0);
  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(errors.invalidModificationErrors == 1);
  assert(cssRule.type() == cssom::CSSRule::IMPORT_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void href() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@import url(\"bluish.css\") projection, tv;"
  );
  cssom::CSSImportRule cssRule = cssom::CSSImportRule::cast(
    styleSheet.cssRules()[0]);


  assertEquals(std::string("bluish.css"), cssRule.href());
}



void media() {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@import url(\"bluish.css\") projection, tv;"
  );
  cssom::CSSImportRule cssRule = cssom::CSSImportRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);
  assertEquals(std::string("projection"), std::string(media[0]));
  assertEquals(std::string("tv"), std::string(media[1]));

  media.deleteMedium("projection");
  media.deleteMedium("tv");
  assert(media.length() == 0);

  cssText = "@import url('bluish.css');";
  assertEquals(cssText, cssRule.cssText());
}



} // unnamed

namespace test {



void cssImportRule() {
  cssText();
  href();
  media();
}



} // test
