#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssom/CSSOM.h>

namespace cssom {



class CSSOM {
  public:
    explicit CSSOM(const char **properties);
    CSSOM(const cssom::CSSOM &copy);
    ~CSSOM();

    cssom::CSSOM& operator=(const cssom::CSSOM &rhs);

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
