#include "test_CSSPageRule.hpp"
#include "test_CSSRule.hpp"
#include "test_CSSStyleRule.hpp"
#include "test_CSSOM.hpp"



int main() {
  test::cssRule();
  test::cssStyleRule();
  test::cssPageRule();
  test::cssom();
  return 0;
}
