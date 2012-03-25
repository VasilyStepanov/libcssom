#ifndef CSSOMPP_CSSSTYLEDECLARATION_HPP
#define CSSOMPP_CSSSTYLEDECLARATION_HPP

#include <cssom/CSSStyleDeclaration.h>

namespace cssom {



class CSSStyleRule;



} // cssom

namespace cssom {



class CSSStyleDeclaration {
  public:
    CSSStyleDeclaration(const cssom::CSSStyleDeclaration &copy);
    ~CSSStyleDeclaration();

    cssom::CSSStyleDeclaration& operator=(
     const cssom::CSSStyleDeclaration &rhs);

    void swap(cssom::CSSStyleDeclaration &rhs);

    const char* cssText() const;
    unsigned long length() const;
    const char* getPropertyValue(const char *property) const;
    const char* getPropertyPriority(const char *property) const;

  private:
    friend class CSSStyleRule;

    CSSOM_CSSStyleDeclaration *_impl;

    explicit CSSStyleDeclaration(CSSOM_CSSStyleDeclaration *impl);
};



} // cssom

#endif // CSSOMPP_CSSSTYLEDECLARATION_HPP