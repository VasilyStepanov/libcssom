#include <cssompp/CSSOM.hpp>

#include "src/CSSOM.h"

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



void CSSOM::setErrorHandler(SAC_ErrorHandler handler) {
  CSSOM_setErrorHandler(_impl, handler);
}



cssom::CSSStyleSheet CSSOM::parseStyleSheet(const char *cssText, int len) {
  CSSOM_CSSStyleSheet *styleSheet = CSSOM_parseStyleSheet(_impl, cssText, len);

  if (styleSheet == NULL) throw std::bad_alloc();

  cssom::CSSStyleSheet wrap(styleSheet);

  CSSOM_CSSStyleSheet_release(styleSheet);

  return wrap;
}



cssom::CSSStyleSheet CSSOM::parseStyleSheet(const std::string &cssText) {
  return parseStyleSheet(cssText.data(), cssText.length());
}



} // cssom
