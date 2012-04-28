#include "test_CSSNamespaceRule.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSNamespaceRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

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
"@namespace svg url('http://www.w3.org/2000/svg');"
  );
  assert(styleSheet.cssRules().length() == 1);
  assert(styleSheet.cssRules()[0].type() == cssom::CSSRule::NAMESPACE_RULE);
  cssom::CSSNamespaceRule cssRule = cssom::CSSNamespaceRule::cast(
    styleSheet.cssRules()[0]);

  /**
   * cssText()
   */

  cssText = "@namespace svg url('http://www.w3.org/2000/svg');";
  assertEquals(cssText, cssRule.cssText());



  /**
   * setCSSText()
   */

  cssRule.setCSSText(
"@namespace foo url('bar');"
  );
  cssText = "@namespace foo url('bar');";
  assert(cssRule.type() == cssom::CSSRule::NAMESPACE_RULE);
  assertEquals(cssText, cssRule.cssText());



  assert(errors.invalidModificationErrors == 0);
  cssRule.setCSSText(
"p {\n"
"  color : green;\n"
"}\n"
  );
  assert(errors.invalidModificationErrors == 1);
  assert(cssRule.type() == cssom::CSSRule::NAMESPACE_RULE);
  assertEquals(cssText, cssRule.cssText());
}



void namespaceURI() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@namespace svg url('http://www.w3.org/2000/svg');"
  );
  cssom::CSSNamespaceRule cssRule = cssom::CSSNamespaceRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("http://www.w3.org/2000/svg"),
    cssRule.namespaceURI());
}



void prefix() {
  test::Errors errors;
  std::string cssText;
  cssom::CSSOM cssom;
  cssom::CSSStyleSheet styleSheet = cssom.parse(
"@namespace svg url('http://www.w3.org/2000/svg');"
  );
  cssom::CSSNamespaceRule cssRule = cssom::CSSNamespaceRule::cast(
    styleSheet.cssRules()[0]);

  assertEquals(std::string("svg"), cssRule.prefix());



  cssRule.setCSSText(
"@namespace url('foo');"
  );

  assert(cssRule.prefix() == NULL);

}



} // unnamed

namespace test {



void cssNamespaceRule() {
  cssText();
  namespaceURI();
  prefix();
}



} // test
