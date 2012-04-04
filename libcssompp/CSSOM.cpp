#include <cssompp/CSSOM.hpp>

#include "src/CSSOM.h"

#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <new>
#include <utility>

namespace cssom {


CSSOM::CSSOM(const char **properties) :
  _impl(CSSOM_create(properties))
{
  if (_impl == NULL) throw std::bad_alloc();
}



CSSOM::CSSOM(const cssom::CSSOM &copy) :
  _impl(copy._impl)
{
  CSSOM_acquire(_impl);
}



CSSOM::~CSSOM() {
  CSSOM_release(_impl);
}



cssom::CSSOM& CSSOM::operator=(const cssom::CSSOM &rhs) {
  if (&rhs == this) return *this;

  cssom::CSSOM(rhs).swap(*this);

  return *this;
}



void CSSOM::swap(cssom::CSSOM &rhs) {
  std::swap(_impl, rhs._impl);
}



void * CSSOM::getUserData() const {
  return CSSOM_getUserData(_impl);
}



void CSSOM::setUserData(void * userData) {
  CSSOM_setUserData(_impl, userData);
}



void CSSOM::setErrorHandler(CSSOM_ErrorHandler handler) {
  CSSOM_setErrorHandler(_impl, handler);
}



cssom::CSSStyleSheet CSSOM::parseCSSStyleSheet(
  const char *cssText, int len) const
{
  CSSOM_CSSStyleSheet *styleSheet;
  
  styleSheet = CSSOM_parseCSSStyleSheet(_impl, cssText, len);
  if (styleSheet == NULL) throw std::bad_alloc();

  cssom::CSSStyleSheet wrap(styleSheet);

  CSSOM_CSSStyleSheet_release(styleSheet);

  return wrap;
}



cssom::CSSStyleSheet CSSOM::parseCSSStyleSheet(
  const std::string &cssText) const
{
  return parseCSSStyleSheet(cssText.data(), cssText.length());
}



cssom::CSSRule CSSOM::parseCSSRule(const char *cssText, int len) const {
  CSSOM_CSSRule *cssRule;
  
  cssRule = CSSOM_parseCSSRule(_impl, cssText, len);
  if (cssRule == NULL) throw std::bad_alloc();

  cssom::CSSRule wrap(cssRule);

  CSSOM_CSSRule_release(cssRule);

  return wrap;
}



cssom::CSSRule CSSOM::parseCSSRule(const std::string &cssText) const {
  return parseCSSRule(cssText.data(), cssText.length());
}



} // cssom
