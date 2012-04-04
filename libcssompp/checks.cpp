#include "checks.hpp"

#include <cssompp/CSSRule.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSNamespaceRule.hpp>

#include <assert.h>

namespace cssom {



template <>
void checkCast<cssom::CSSRule, cssom::CSSStyleRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSStyleRule::STYLE_RULE);
}




template <>
void checkCast<cssom::CSSRule, cssom::CSSNamespaceRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSStyleRule::NAMESPACE_RULE);
}



} // cssom
