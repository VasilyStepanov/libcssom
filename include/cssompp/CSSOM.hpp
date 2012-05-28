#ifndef CSSOMPP_CSSOM_HPP
#define CSSOMPP_CSSOM_HPP

#include <cssom/CSSOM.h>

#include <string>

namespace cssom {



class CSSRule;

class CSSStyleSheet;

class Selector;



}

namespace cssom {



class CSSOM {
  public:
    CSSOM();
    CSSOM(const cssom::CSSOM &copy);
    ~CSSOM();

    cssom::CSSOM& operator=(const cssom::CSSOM &rhs);

    bool operator==(const cssom::CSSOM &rhs) const;

    void swap(cssom::CSSOM &rhs);

    void * getUserData() const;
    void setUserData(void * userData);
    const CSSOM_DOMAPI* getDOMAPI() const;
    void setDOMAPI(const CSSOM_DOMAPI *domapi);
    void setErrorHandler(CSSOM_ErrorHandler handler);

    cssom::CSSStyleSheet parse(const char *cssText, int len) const;
    cssom::CSSStyleSheet parse(const std::string &cssText) const;

    cssom::Selector parseSelector(const char *selectorText, int len) const;
    cssom::Selector parseSelector(const std::string &selectorText) const;

  private:
    ::CSSOM *_impl;
};



} // cssom

#endif // CSSOMPP_CSSOM_HPP
