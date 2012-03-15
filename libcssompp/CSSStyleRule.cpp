#include <cssompp/CSSStyleRule.hpp>

#include <cssom/CSSStyleRule.h>

namespace cssom {



const char* CSSStyleRule::selectorText() const {
  return CSSOM_CSSStyleRule_selectorText(
    reinterpret_cast<CSSOM_CSSStyleRule*>(_impl));
}



cssom::CSSStyleDeclaration CSSStyleRule::style() {
  return cssom::CSSStyleDeclaration(CSSOM_CSSStyleRule_style(
    reinterpret_cast<CSSOM_CSSStyleRule*>(_impl)));
}



} // cssom
