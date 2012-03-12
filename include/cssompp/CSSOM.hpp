#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssompp/CSSStyleSheet.hpp>

#include <cssom/CSSOM.h>

#include <string>

namespace cssom {



class CSSOM {
  public:
    explicit CSSOM(const char **properties);
    CSSOM(const cssom::CSSOM &copy);
    ~CSSOM();

    cssom::CSSOM& operator=(const cssom::CSSOM &rhs);

    void swap(cssom::CSSOM &rhs);
    cssom::CSSStyleSheet parse(const char *cssText, int len);
    cssom::CSSStyleSheet parse(const std::string &cssText);

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
