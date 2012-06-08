#ifndef CSSOMPP_CSS_STYLE_DECLARATION_HPP
#define CSSOMPP_CSS_STYLE_DECLARATION_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclaration.idl'
 */



#include <cssom/typedefs.h>

namespace cssom {



class CSSRule;



class CSSStyleDeclarationValue;



} // cssom

namespace cssom {



class CSSStyleDeclaration {
  public:
    typedef CSSOM_CSSStyleDeclaration * Impl;

    CSSStyleDeclaration();
    explicit CSSStyleDeclaration(cssom::CSSStyleDeclaration::Impl impl);
    CSSStyleDeclaration(const cssom::CSSStyleDeclaration &copy);
    ~CSSStyleDeclaration();

    cssom::CSSStyleDeclaration& operator=(const cssom::CSSStyleDeclaration &rhs);

    bool operator==(const cssom::CSSStyleDeclaration &rhs) const;

    bool isNull() const;

    void swap(cssom::CSSStyleDeclaration &rhs);

    const char * cssText() const;
    void setCSSText(const char * cssText);

    unsigned long length() const;

    const char * item(unsigned long index);

    const char * getPropertyValue(const char * property);

    const char * getPropertyPriority(const char * property);

    void setProperty(const char * property, const char * value);

    void setProperty(const char * property, const char * value, const char * priority);

    const char * removeProperty(const char * property);

    cssom::CSSStyleDeclarationValue values() const;

    cssom::CSSRule parentRule() const;

    const char * azimuth() const;
    void setAzimuth(const char * azimuth);

    const char * background() const;
    void setBackground(const char * background);

    const char * backgroundAttachment() const;
    void setBackgroundAttachment(const char * backgroundAttachment);

    const char * backgroundColor() const;
    void setBackgroundColor(const char * backgroundColor);

    const char * backgroundImage() const;
    void setBackgroundImage(const char * backgroundImage);

    const char * backgroundPosition() const;
    void setBackgroundPosition(const char * backgroundPosition);

    const char * backgroundRepeat() const;
    void setBackgroundRepeat(const char * backgroundRepeat);

    const char * borderCollapse() const;
    void setBorderCollapse(const char * borderCollapse);

    const char * borderColor() const;
    void setBorderColor(const char * borderColor);

    const char * borderSpacing() const;
    void setBorderSpacing(const char * borderSpacing);

    const char * borderTopColor() const;
    void setBorderTopColor(const char * borderTopColor);

    const char * borderRightColor() const;
    void setBorderRightColor(const char * borderRightColor);

    const char * borderBottomColor() const;
    void setBorderBottomColor(const char * borderBottomColor);

    const char * borderLeftColor() const;
    void setBorderLeftColor(const char * borderLeftColor);

  protected:
    cssom::CSSStyleDeclaration::Impl _impl;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_DECLARATION_HPP
