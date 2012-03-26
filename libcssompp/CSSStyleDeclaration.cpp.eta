#include <cssompp/CSSStyleDeclaration.hpp>

#include "src/CSSStyleDeclaration.h"

#include <utility>

namespace cssom {



CSSStyleDeclaration::CSSStyleDeclaration(CSSOM_CSSStyleDeclaration *impl) :
  _impl(impl)
{}



CSSStyleDeclaration::CSSStyleDeclaration(
  const cssom::CSSStyleDeclaration &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSStyleDeclaration__acquire(_impl);
}



CSSStyleDeclaration::~CSSStyleDeclaration() {
  CSSOM_CSSStyleDeclaration__release(_impl);
}



cssom::CSSStyleDeclaration& CSSStyleDeclaration::operator=(
  const cssom::CSSStyleDeclaration &rhs)
{
  if (&rhs == this) return *this;

  cssom::CSSStyleDeclaration(rhs).swap(*this);

  return *this;
}



void CSSStyleDeclaration::swap(cssom::CSSStyleDeclaration &rhs) {
  std::swap(_impl, rhs._impl);
}



const char* CSSStyleDeclaration::cssText() const {
  return CSSOM_CSSStyleDeclaration_cssText(_impl);
}



unsigned long CSSStyleDeclaration::length() const {
  return CSSOM_CSSStyleDeclaration_length(_impl);
}



const char* CSSStyleDeclaration::getPropertyValue(const char *property) const {
  return CSSOM_CSSStyleDeclaration_getPropertyValue(_impl, property);
}



const char* CSSStyleDeclaration::getPropertyPriority(
  const char *property) const
{
  return CSSOM_CSSStyleDeclaration_getPropertyPriority(_impl, property);
}



} // cssom
