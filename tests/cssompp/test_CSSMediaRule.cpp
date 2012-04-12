#include "test_CSSMediaRule.hpp"

#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



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

  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);

  assert(cssRule.cssRules().size() == 1);
  assert(cssRule.cssRules()[0].type() == cssom::CSSRule::STYLE_RULE);
}



} // unnamed

namespace test {



void cssMediaRule() {
  cssRules();
}



} // test
