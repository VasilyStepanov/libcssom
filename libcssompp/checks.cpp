#include "checks.hpp"

#include <cssompp/CSSFontFaceRule.hpp>
#include <cssompp/CSSImportRule.hpp>
#include <cssompp/CSSMediaRule.hpp>
#include <cssompp/CSSNamespaceRule.hpp>
#include <cssompp/CSSPageRule.hpp>
#include <cssompp/CSSRule.hpp>
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
void checkCast<cssom::CSSRule, cssom::CSSFontFaceRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::FONT_FACE_RULE);
}



template <>
void checkCast<cssom::CSSRule, cssom::CSSImportRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::IMPORT_RULE);
}



template <>
void checkCast<cssom::CSSRule, cssom::CSSMediaRule>(
  const cssom::CSSRule &cssRule)
{
  assert(cssRule.type() == cssom::CSSRule::MEDIA_RULE);
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
