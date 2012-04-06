#ifndef CSSOMPP_CSS_STYLE_DECLARATION_HPP
#define CSSOMPP_CSS_STYLE_DECLARATION_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclaration.idl'
 */



#include <cssom/typedefs.h>


namespace cssom {



class CSSStyleDeclaration {
  public:
    typedef CSSOM_CSSStyleDeclaration * C;

    CSSStyleDeclaration();
    explicit CSSStyleDeclaration(CSSOM_CSSStyleDeclaration * impl);

    bool operator==(
     const cssom::CSSStyleDeclaration &rhs) const;

    const char * cssText() const;

    unsigned long length() const;

    const char * getPropertyValue(const char * property);

    const char * getPropertyPriority(const char * property);

  protected:
    CSSOM_CSSStyleDeclaration * _impl;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_DECLARATION_HPP
