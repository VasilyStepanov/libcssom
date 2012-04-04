#include <cssompp/CSSRule.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/CSSRule.h>

#include "checks.hpp"

#include <utility>

namespace cssom {



CSSRule::CSSRule(CSSOM_CSSRule * impl) :
  _impl(impl)
{
  CSSOM_CSSRule_acquire(_impl);
}



CSSRule::CSSRule(const cssom::CSSRule &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSRule_acquire(_impl);
}



CSSRule::~CSSRule() {
  CSSOM_CSSRule_release(_impl);
}



cssom::CSSRule& CSSRule::operator=(
  const cssom::CSSRule &rhs)
{
  if (&rhs == this) return *this;

  cssom::CSSRule(rhs).swap(*this);

  return *this;
}



void CSSRule::swap(cssom::CSSRule &rhs) {
  std::swap(_impl, rhs._impl);
}



unsigned short CSSRule::STYLE_RULE = CSSOM_CSSRule_STYLE_RULE;



unsigned short CSSRule::IMPORT_RULE = CSSOM_CSSRule_IMPORT_RULE;



unsigned short CSSRule::MEDIA_RULE = CSSOM_CSSRule_MEDIA_RULE;



unsigned short CSSRule::FONT_FACE_RULE = CSSOM_CSSRule_FONT_FACE_RULE;



unsigned short CSSRule::PAGE_RULE = CSSOM_CSSRule_PAGE_RULE;



unsigned short CSSRule::NAMESPACE_RULE = CSSOM_CSSRule_NAMESPACE_RULE;



unsigned short CSSRule::type() const {
  return CSSOM_CSSRule_type(_impl);
}



const char * CSSRule::cssText() const {
  return CSSOM_CSSRule_cssText(_impl);
}



void CSSRule::setCSSText(const char * cssText) {
  CSSOM_CSSRule_setCSSText(_impl, cssText);
}



} // cssom
