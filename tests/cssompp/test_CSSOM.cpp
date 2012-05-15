#include "test_CSSOM.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp.hpp>

#include <assert.h>

namespace {



void parse() {
  cssom::CSSOM cssom;

  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
"  color : green\n"
"}\n"
  );

  cssom::CSSRuleList cssRules = styleSheet.cssRules();
  assert(cssRules.length() == 1);

  cssom::CSSRule cssRule = cssRules[0];
  assert(cssRule.type() == cssom::CSSRule::STYLE_RULE);

  cssom::CSSStyleRule &styleRule = static_cast<cssom::CSSStyleRule&>(cssRule);

  assert(std::string(styleRule.selectorText()) == "p");

  cssom::CSSStyleDeclaration style = styleRule.style();
  assert(style.length() == 1);

  assert(std::string(style.getPropertyValue("color")) == "green");
}



void parseSelector() {
  test::Errors errors;
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom.setUserData(&errors);
  cssom.setErrorHandler(test::errorHandler);
  cssom::Selector selector = cssom.parseSelector("p");

  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());



  assert(errors.syntaxErrors == 0);
  selector = cssom.parseSelector("& invalid");
  assert(selector.isNull() == true);
  assert(errors.syntaxErrors == 1);
}



void malformedProperty() {
  std::string cssText;
  cssom::CSSOM cssom;

  cssom::CSSStyleSheet styleSheet = cssom.parse(
"p {\n"
"  aaa : bbb;\n"
"  color : green;\n"
"  xxx : yyy;\n"
"}\n"
  );

  cssom::CSSRuleList cssRules = styleSheet.cssRules();
  assert(cssRules.length() == 1);

  cssom::CSSRule cssRule = cssRules[0];
  assert(cssRule.type() == cssom::CSSRule::STYLE_RULE);

  cssom::CSSStyleRule &styleRule = static_cast<cssom::CSSStyleRule&>(cssRule);

  cssText = "p { color : green; }" ;
  assertEquals(cssText, styleRule.cssText());
}



} // unnamed

namespace test {



void cssom() {
  parse();
  parseSelector();
  malformedProperty();
}



} // test
