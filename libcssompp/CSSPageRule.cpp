#include <cssompp/CSSPageRule.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSPageRule.idl'
 */



#include <cssom/CSSPageRule.h>

#include <cssompp/CSSStyleDeclaration.hpp>

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



CSSPageRule::CSSPageRule(CSSOM_CSSPageRule * impl) :
  CSSRule((CSSOM_CSSRule *)impl)
{}



const char * CSSPageRule::selectorText() const {
  return CSSOM_CSSPageRule_selectorText(reinterpret_cast<CSSOM_CSSPageRule*>(_impl));
}



cssom::CSSStyleDeclaration CSSPageRule::style() const {
  return cssom::CSSStyleDeclaration(CSSOM_CSSPageRule_style(reinterpret_cast<CSSOM_CSSPageRule*>(_impl)));
}



} // cssom
