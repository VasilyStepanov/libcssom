#include <cssompp/CSSPageRule.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/CSSPageRule.h>

#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/Selector.hpp>

#include "checks.hpp"

#include <utility>

namespace cssom {



CSSPageRule CSSPageRule::cast(
  const cssom::CSSRule & cssRule)
{
#ifndef NDEBUG
  cssom::checkCast<cssom::CSSRule, cssom::CSSPageRule>(cssRule);
#endif // NDEBUG
  return static_cast<const cssom::CSSPageRule &>(cssRule);
}



CSSPageRule & CSSPageRule::cast(
  cssom::CSSRule & cssRule)
{
#ifndef NDEBUG
  cssom::checkCast<cssom::CSSRule, cssom::CSSPageRule>(cssRule);
#endif // NDEBUG
  return static_cast<cssom::CSSPageRule &>(cssRule);
}



CSSPageRule::CSSPageRule() :
  CSSRule()
{}



CSSPageRule::CSSPageRule(cssom::CSSPageRule::Impl impl) :
  CSSRule((cssom::CSSRule::Impl)impl)
{}



cssom::Selector CSSPageRule::selector() const {
  return cssom::Selector(CSSOM_CSSPageRule_selector(reinterpret_cast<cssom::CSSPageRule::Impl>(_impl)));
}



const char * CSSPageRule::selectorText() const {
  return CSSOM_CSSPageRule_selectorText(reinterpret_cast<cssom::CSSPageRule::Impl>(_impl));
}



void CSSPageRule::setSelectorText(const char * selectorText) {
  CSSOM_CSSPageRule_setSelectorText(reinterpret_cast<cssom::CSSPageRule::Impl>(_impl), selectorText);
}



cssom::CSSStyleDeclaration CSSPageRule::style() const {
  return cssom::CSSStyleDeclaration(CSSOM_CSSPageRule_style(reinterpret_cast<cssom::CSSPageRule::Impl>(_impl)));
}



} // cssom
