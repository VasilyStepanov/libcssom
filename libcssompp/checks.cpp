#include "checks.hpp"

#include <cssompp/CSSRule.hpp>
#include <cssompp/CSSNamespaceRule.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSStyleRule.hpp>

#include <assert.h>

namespace cssom {



template <>
void checkCast<cssom::CSSRule, cssom::CSSStyleRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::STYLE_RULE);
}




template <>
void checkCast<cssom::CSSRule, cssom::CSSNamespaceRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::NAMESPACE_RULE);
}




template <>
void checkCast<cssom::CSSRule, cssom::CSSPageRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::PAGE_RULE);
}



} // cssom
