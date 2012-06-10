#include "test_MediaList.hpp"

#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/MediaList.hpp>

#include "Errors.hpp"
#include "utility.hpp"

#include <iostream>

#include <assert.h>

namespace {



void mediaText(void) {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  cssText = "screen and (min-width: 400px) and (max-width: 700px), projection";
  assertEquals(cssText, media.mediaText());
  assertEquals(cssText, std::string(media).c_str());



  media.setMediaText("all");
  cssText = "all";
  assertEquals(cssText, media.mediaText());



  media.setMediaText("");
  cssText = "";
  assertEquals(cssText, media.mediaText());



  assert(errors.syntaxErrors == 0);
  media.setMediaText("screen, & projection");
  cssText = "screen";
  assertEquals(cssText, media.mediaText());
  assert(errors.syntaxErrors == 1);
}



void length(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);
}



void item(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);

  cssText = "screen and (min-width: 400px) and (max-width: 700px)";
  assertEquals(cssText, media.item(0));
  assertEquals(cssText, media[0]);

  cssText = "projection";
  assertEquals(cssText, media.item(1));
  assertEquals(cssText, media[1]);
}



void unique(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom.setErrorHandler(test::errorHandler);
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen, screen, screen, Screen {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);

  cssText = "screen";
  assertEquals(cssText, media.item(0));

  cssText = "Screen";
  assertEquals(cssText, media.item(1));
}



void sacCare(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::MediaList media;
  {
    cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
    cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
      styleSheet.cssRules()[0]);
    media = cssRule.media();
  }

  cssText = "screen and (min-width: 400px) and (max-width: 700px), projection";
  assertEquals(cssText, std::string(media).c_str());
}



void appendMedium(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);

  media.appendMedium("all");
  assert(media.length() == 3);

  media.appendMedium(
    "projection and (min-width: 400px), projection and (max-width: 700px)");
  assert(media.length() == 3);

  media.appendMedium("screen");
  assert(media.length() == 4);

  media.appendMedium("screen and (min-width: 400px) and (max-width: 700px)");
  assert(media.length() == 4);

  media.appendMedium("screen and (min-width: 400px) and (max-width: 701px)");
  assert(media.length() == 5);
}



void deleteMedium(void) {
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@media screen and (min-width: 400px) and (max-width: 700px), projection {\n"
"  p {\n"
"    color : green;\n"
"  }\n"
"}\n"
  );
  cssom::CSSMediaRule cssRule = cssom::CSSMediaRule::cast(
    styleSheet.cssRules()[0]);
  cssom::MediaList media = cssRule.media();

  assert(media.length() == 2);

  media.deleteMedium("projection");
  assert(media.length() == 1);

  media.deleteMedium("all &");
  assert(media.length() == 1);

  media.deleteMedium("screen and (min-width: 400px) and (max-width: 700px)");
  assert(media.length() == 0);
}



} // unnamed

namespace test {



void mediaList() {
  mediaText();
  length();
  item();
  unique();
  sacCare();
  appendMedium();
  deleteMedium();
}



} // test
