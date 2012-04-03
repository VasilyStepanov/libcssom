#include "test_CSSOM.hpp"

#include <cssom/CSSProperty.h>
#include <cssompp.hpp>

#include <assert.h>

namespace {



void basics() {
  cssom::CSSOM cssom;

  cssom::CSSStyleSheet styleSheet = cssom.parseStyleSheet(
"p {\n"
"  color : green\n"
"}\n"
  );

  cssom::CSSRuleList cssRules = styleSheet.cssRules();
  assert(cssRules.size() == 1);

  cssom::CSSRule cssRule = cssRules[0];
  assert(cssRule.type() == CSSOM_CSSRule_STYLE_RULE);

  cssom::CSSStyleRule &styleRule = static_cast<cssom::CSSStyleRule&>(cssRule);

  assert(std::string(styleRule.selectorText()) == "p");

  cssom::CSSStyleDeclaration style = styleRule.style();
  assert(style.length() == 1);

  assert(std::string(style.getPropertyValue("color")) == "green");
}



} // unnamed

namespace test {



void CSSOM() {
  basics();
}



} // test
