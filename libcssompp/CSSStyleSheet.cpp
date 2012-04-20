#include <cssompp/CSSStyleSheet.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleSheet.idl'
 */



#include <cssom/CSSStyleSheet.h>

#include "checks.hpp"

#include <utility>

namespace cssom {



CSSStyleSheet::CSSStyleSheet() :
  _impl(NULL)
{}



CSSStyleSheet::CSSStyleSheet(CSSOM_CSSStyleSheet * impl) :
  _impl(impl)
{
  CSSOM_CSSStyleSheet_acquire(_impl);
}



CSSStyleSheet::CSSStyleSheet(const cssom::CSSStyleSheet &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSStyleSheet_acquire(_impl);
}



CSSStyleSheet::~CSSStyleSheet() {
  CSSOM_CSSStyleSheet_release(_impl);
}



cssom::CSSStyleSheet& CSSStyleSheet::operator=(
  const cssom::CSSStyleSheet &rhs)
{
  if (&rhs == this) return *this;

  cssom::CSSStyleSheet(rhs).swap(*this);

  return *this;
}



bool CSSStyleSheet::operator==(
  const cssom::CSSStyleSheet &rhs) const
{
  return _impl == rhs._impl;
}



bool CSSStyleSheet::isNull() const {
  return _impl == NULL;
}



void CSSStyleSheet::swap(cssom::CSSStyleSheet &rhs) {
  std::swap(_impl, rhs._impl);
}



cssom::CSSRuleList CSSStyleSheet::cssRules() const {
  return cssom::CSSRuleList(CSSOM_CSSStyleSheet_cssRules(_impl));
}



unsigned long CSSStyleSheet::insertRule(const char * rule, unsigned long index) {
  return CSSOM_CSSStyleSheet_insertRule(_impl, rule, index);
}



void CSSStyleSheet::deleteRule(unsigned long index) {
  return CSSOM_CSSStyleSheet_deleteRule(_impl, index);
}



} // cssom
