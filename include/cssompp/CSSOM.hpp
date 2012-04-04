#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssom/CSSOM.h>
#include <cssom/CSSProperty.h>

#include <string>

namespace cssom {



class CSSStyleRule;

class CSSStyleSheet;



}

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
    void setErrorHandler(CSSOM_ErrorHandler handler);

    cssom::CSSStyleSheet parseCSSStyleSheet(const char *cssText, int len) const;
    cssom::CSSStyleSheet parseCSSStyleSheet(const std::string &cssText) const;
    cssom::CSSStyleRule parseCSSStyleRule(const char *cssText, int len) const;
    cssom::CSSStyleRule parseCSSStyleRule(const std::string &cssText) const;

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
