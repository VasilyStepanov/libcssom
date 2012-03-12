#include <cssompp/CSSStyleRule.hpp>

#include <cssom/CSSStyleRule.h>

namespace cssom {



const char* CSSStyleRule::selectorText() const {
  return CSSOM_CSSStyleRule_selectorText((CSSOM_CSSStyleRule*)_impl);
}



cssom::CSSStyleDeclaration CSSStyleRule::style() {
  return cssom::CSSStyleDeclaration(CSSOM_CSSStyleRule_style(
    (CSSOM_CSSStyleRule*)_impl));
}



} // cssom
