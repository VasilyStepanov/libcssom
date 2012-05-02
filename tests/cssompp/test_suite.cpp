#include "test_CSSFontFaceRule.hpp"
#include "test_CSSImportRule.hpp"
#include "test_CSSMediaRule.hpp"
#include "test_CSSNamespaceRule.hpp"
#include "test_CSSPageRule.hpp"
#include "test_CSSPropertyValue.hpp"
#include "test_CSSRule.hpp"
#include "test_CSSStyleDeclaration.hpp"
#include "test_CSSStyleDeclarationValue.hpp"
#include "test_CSSStyleRule.hpp"
#include "test_CSSStyleSheet.hpp"
#include "test_CSSOM.hpp"
#include "test_MediaList.hpp"



int main() {
  test::cssom();
  test::cssRule();
  test::cssStyleRule();
  test::cssPageRule();
  test::cssMediaRule();
  test::mediaList();
  test::cssNamespaceRule();
  test::cssFontFaceRule();
  test::cssImportRule();
  test::cssStyleSheet();
  test::cssStyleDeclaration();
  test::cssStyleDeclarationValue();
  test::cssPropertyValue();
  return 0;
}
