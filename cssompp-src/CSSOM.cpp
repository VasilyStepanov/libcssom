#include <cssompp/CSSOM.hpp>

#include "cssom-src/CSSOM.h"

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
  CSSOM__acquire(_impl);
}



CSSOM::~CSSOM() {
  CSSOM__release(_impl);
}



cssom::CSSOM& CSSOM::operator=(const cssom::CSSOM &rhs) {
  if (&rhs == this) return *this;

  cssom::CSSOM(rhs).swap(*this);

  return *this;
}



void CSSOM::swap(cssom::CSSOM &rhs) {
  std::swap(_impl, rhs._impl);
}



} // cssom
