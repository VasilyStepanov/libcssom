#ifndef CSSOMPP_CSS_STYLE_DECLARATION_VALUE_HPP
#define CSSOMPP_CSS_STYLE_DECLARATION_VALUE_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclarationValue.idl'
 */



#include <cssom/typedefs.h>

namespace cssom {



class CSSPropertyValue;



} // cssom

namespace cssom {



class CSSStyleDeclarationValue {
  public:
    typedef CSSOM_CSSStyleDeclarationValue * C;

    CSSStyleDeclarationValue();
    explicit CSSStyleDeclarationValue(CSSOM_CSSStyleDeclarationValue * impl);
    CSSStyleDeclarationValue(const cssom::CSSStyleDeclarationValue &copy);
    ~CSSStyleDeclarationValue();

    cssom::CSSStyleDeclarationValue& operator=(const cssom::CSSStyleDeclarationValue &rhs);

    bool operator==(const cssom::CSSStyleDeclarationValue &rhs) const;

    bool isNull() const;

    void swap(cssom::CSSStyleDeclarationValue &rhs);

    unsigned long length() const;

    const char * item(unsigned long index);

    cssom::CSSPropertyValue getProperty(const char * property);

    void setProperty(const char * property, const char * value);

    void setProperty(const char * property, const char * value, const char * priority);

    const char * removeProperty(const char * property);

  protected:
    CSSOM_CSSStyleDeclarationValue * _impl;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_DECLARATION_VALUE_HPP
