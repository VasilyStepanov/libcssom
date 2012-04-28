#include "test_MediaList.hpp"

#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/MediaList.hpp>

#include "Errors.hpp"
#include "utility.hpp"

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
}



} // unnamed

namespace test {



void mediaList() {
  mediaText();
}



} // test
