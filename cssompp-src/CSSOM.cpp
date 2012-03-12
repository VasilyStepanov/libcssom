#include <cssompp/CSSOM.hpp>

#include "cssom-src/CSSOM.h"

#include <new>

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



} // cssom
