#include "test_CSSStyleRule.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>

#include <assert.h>

namespace {



cssom::CSSStyleRule styleRule(const cssom::CSSOM &cssom) {
  return cssom.parseCSSStyleRule(
"p {\n"
" color : green;\n"
"}\n"
  );
}



void consts() {
  assert(cssom::CSSStyleRule::STYLE_RULE == 1);
  assert(cssom::CSSStyleRule::IMPORT_RULE == 3);
  assert(cssom::CSSStyleRule::MEDIA_RULE == 4);
  assert(cssom::CSSStyleRule::FONT_FACE_RULE == 5);
  assert(cssom::CSSStyleRule::PAGE_RULE == 6);
  assert(cssom::CSSStyleRule::NAMESPACE_RULE == 10);
}



void type() {
  cssom::CSSOM cssom;
  cssom::CSSStyleRule style = styleRule(cssom);

  assert(style.type() == cssom::CSSStyleRule::STYLE_RULE);
}



} // unnamed

namespace test {



void cssStyleRule() {
  consts();
  // type();
}



} // test
