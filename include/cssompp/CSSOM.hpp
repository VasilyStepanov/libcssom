#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssom/CSSOM.h>
#include <cssom/CSSProperty.h>

#include <string>

namespace cssom {



class CSSRule;

class CSSStyleSheet;



}

namespace cssom {



class CSSOM {
  public:
    explicit CSSOM(const char **properties = CSSOM_CSSProperties);
    CSSOM(const cssom::CSSOM &copy);
    ~CSSOM();

    cssom::CSSOM& operator=(const cssom::CSSOM &rhs);

    bool operator==(const cssom::CSSOM &rhs) const;

    void swap(cssom::CSSOM &rhs);

    void * getUserData() const;
    void setUserData(void * userData);
    void setErrorHandler(CSSOM_ErrorHandler handler);

    cssom::CSSStyleSheet parse(const char *cssText, int len) const;
    cssom::CSSStyleSheet parse(const std::string &cssText) const;

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
