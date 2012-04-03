#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssompp/CSSStyleSheet.hpp>

#include <cssom/CSSOM.h>
#include <cssom/CSSProperty.h>

#include <string>

namespace cssom {



class CSSOM {
  public:
    explicit CSSOM(const char **properties = CSSOM_CSSProperties);
    CSSOM(const cssom::CSSOM &copy);
    ~CSSOM();

    cssom::CSSOM& operator=(const cssom::CSSOM &rhs);

    void swap(cssom::CSSOM &rhs);

    void * getUserData() const;
    void setUserData(void * userData);
    void setErrorHandler(SAC_ErrorHandler handler);

    cssom::CSSStyleSheet parseStyleSheet(const char *cssText, int len);
    cssom::CSSStyleSheet parseStyleSheet(const std::string &cssText);

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
