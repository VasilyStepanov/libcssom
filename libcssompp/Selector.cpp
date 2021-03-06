#include <cssompp/Selector.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/Selector.h>

#include <cssompp/CSSRule.hpp>

#include "checks.hpp"

#include <utility>

namespace cssom {



Selector::Selector() :
  _impl(NULL)
{}



Selector::Selector(cssom::Selector::Impl impl) :
  _impl(impl)
{
  CSSOM_Selector_acquire(_impl);
}



Selector::Selector(const cssom::Selector &copy) :
  _impl(copy._impl)
{
  CSSOM_Selector_acquire(_impl);
}



Selector::~Selector() {
  CSSOM_Selector_release(_impl);
}



cssom::Selector& Selector::operator=(
  const cssom::Selector &rhs)
{
  if (&rhs == this) return *this;

  cssom::Selector(rhs).swap(*this);

  return *this;
}



bool Selector::operator==(
  const cssom::Selector &rhs) const
{
  return _impl == rhs._impl;
}



bool Selector::isNull() const {
  return _impl == NULL;
}



void Selector::swap(cssom::Selector &rhs) {
  std::swap(_impl, rhs._impl);
}



const char * Selector::selectorText() const {
  return CSSOM_Selector_selectorText(_impl);
}



void Selector::setSelectorText(const char * selectorText) {
  CSSOM_Selector_setSelectorText(_impl, selectorText);
}



cssom::CSSRule Selector::parentRule() const {
  return cssom::CSSRule(CSSOM_Selector_parentRule(_impl));
}



unsigned long Selector::specificity() const {
  return CSSOM_Selector_specificity(_impl);
}



void Selector::select(void * root, void * selection) {
  return CSSOM_Selector_select(_impl, root, selection);
}



} // cssom
