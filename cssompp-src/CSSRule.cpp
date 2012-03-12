#include <cssompp/CSSRule.hpp>

#include "cssom-src/CSSRule.h"

#include <utility>

namespace cssom {



CSSRule::CSSRule(CSSOM_CSSRule *impl) :
  _impl(impl)
{}



CSSRule::CSSRule(const cssom::CSSRule &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSRule__acquire(_impl);
}



CSSRule::~CSSRule() {
  CSSOM_CSSRule__release(_impl);
}



cssom::CSSRule& CSSRule::operator=(const cssom::CSSRule &rhs) {
  if (&rhs == this) return *this;

  cssom::CSSRule(rhs).swap(*this);

  return *this;
}



void CSSRule::swap(cssom::CSSRule &rhs) {
  std::swap(_impl, rhs._impl);
}



cssom::CSSRuleType CSSRule::type() const {
  return CSSOM_CSSRule_type(_impl);
}



} // cssom
