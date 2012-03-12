#include <cssompp/CSSRuleList.hpp>

#include "cssom-src/CSSRuleList.h"

#include <utility>

namespace cssom {



CSSRuleList::CSSRuleList(CSSOM_CSSRuleList *impl) :
  _impl(impl)
{}



CSSRuleList::CSSRuleList(const cssom::CSSRuleList &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSRuleList__acquire(_impl);
}



CSSRuleList::~CSSRuleList() {
  CSSOM_CSSRuleList__release(_impl);
}



cssom::CSSRuleList& CSSRuleList::operator=(const cssom::CSSRuleList &rhs) {
  if (&rhs == this) return *this;

  cssom::CSSRuleList(rhs).swap(*this);

  return *this;
}



void CSSRuleList::swap(cssom::CSSRuleList &rhs) {
  std::swap(_impl, rhs._impl);
}



size_t CSSRuleList::size() const {
  return CSSOM_CSSRuleList_size(_impl);
}



cssom::CSSRule CSSRuleList::operator[](size_t index) const {
  return cssom::CSSRule(CSSOM_CSSRuleList_at(_impl, index));
}



} // cssom
