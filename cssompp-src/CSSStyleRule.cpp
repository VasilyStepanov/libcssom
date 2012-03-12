#include <cssompp/CSSStyleRule.hpp>

#include <cssom/CSSStyleRule.h>

namespace cssom {



cssom::CSSStyleDeclaration CSSStyleRule::style() {
  return cssom::CSSStyleDeclaration(CSSOM_CSSStyleRule_style(
    (CSSOM_CSSStyleRule*)_impl));
}



} // cssom
