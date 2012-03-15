#include <cssompp/CSSStyleSheet.hpp>

#include "src/CSSStyleSheet.h"

#include <utility>

namespace cssom {



CSSStyleSheet::CSSStyleSheet(CSSOM_CSSStyleSheet *impl) :
  _impl(impl)
{}



CSSStyleSheet::CSSStyleSheet(const cssom::CSSStyleSheet &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSStyleSheet__acquire(_impl);
}



CSSStyleSheet::~CSSStyleSheet() {
  CSSOM_CSSStyleSheet__release(_impl);
}



cssom::CSSStyleSheet& CSSStyleSheet::operator=(
  const cssom::CSSStyleSheet &rhs)
{
  if (&rhs == this) return *this;

  cssom::CSSStyleSheet(rhs).swap(*this);

  return *this;
}



void CSSStyleSheet::swap(cssom::CSSStyleSheet &rhs) {
  std::swap(_impl, rhs._impl);
}



cssom::CSSRuleList CSSStyleSheet::cssRules() const {
  return cssom::CSSRuleList(CSSOM_CSSStyleSheet_cssRules(_impl));
}



} // cssom
