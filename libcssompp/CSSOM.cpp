#include <cssompp/CSSOM.hpp>

#include "src/CSSOM.h"

#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/Selector.hpp>
#include <cssom/CSSStyleSheet.h>
#include <cssom/Selector.h>

#include <new>
#include <utility>

namespace cssom {


CSSOM::CSSOM() :
  _impl(CSSOM_create())
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



bool CSSOM::operator==(const cssom::CSSOM &rhs) const {
  return _impl == rhs._impl;
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



const CSSOM_DOMAPI* CSSOM::getDOMAPI() const {
  return CSSOM_getDOMAPI(_impl);
}



void CSSOM::setDOMAPI(const CSSOM_DOMAPI *domapi) {
  CSSOM_setDOMAPI(_impl, domapi);
}



void CSSOM::setErrorHandler(CSSOM_ErrorHandler handler) {
  CSSOM_setErrorHandler(_impl, handler);
}



cssom::CSSStyleSheet CSSOM::parse(const char *cssText, int len) const {
  CSSOM_CSSStyleSheet *styleSheet;
  
  styleSheet = CSSOM_parse(_impl, cssText, len);
  if (styleSheet == NULL) throw std::bad_alloc();

  cssom::CSSStyleSheet wrap(styleSheet);

  CSSOM_CSSStyleSheet_release(styleSheet);

  return wrap;
}



cssom::CSSStyleSheet CSSOM::parse(const std::string &cssText) const {
  return parse(cssText.data(), cssText.length());
}



cssom::Selector CSSOM::parseSelector(const char *selectorText, int len) const {
  CSSOM_Selector *selector;
  
  selector = CSSOM_parseSelector(_impl, selectorText, len);

  cssom::Selector wrap(selector);

  CSSOM_Selector_release(selector);

  return wrap;
}



cssom::Selector CSSOM::parseSelector(const std::string &selectorText) const {
  return parseSelector(selectorText.data(), selectorText.length());
}



} // cssom
