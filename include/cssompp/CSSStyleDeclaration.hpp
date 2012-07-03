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

    const char * border() const;
    void setBorder(const char * border);

    const char * borderCollapse() const;
    void setBorderCollapse(const char * borderCollapse);

    const char * borderColor() const;
    void setBorderColor(const char * borderColor);

    const char * borderSpacing() const;
    void setBorderSpacing(const char * borderSpacing);

    const char * borderStyle() const;
    void setBorderStyle(const char * borderStyle);

    const char * borderTop() const;
    void setBorderTop(const char * borderTop);

    const char * borderRight() const;
    void setBorderRight(const char * borderRight);

    const char * borderBottom() const;
    void setBorderBottom(const char * borderBottom);

    const char * borderLeft() const;
    void setBorderLeft(const char * borderLeft);

    const char * borderTopColor() const;
    void setBorderTopColor(const char * borderTopColor);

    const char * borderRightColor() const;
    void setBorderRightColor(const char * borderRightColor);

    const char * borderBottomColor() const;
    void setBorderBottomColor(const char * borderBottomColor);

    const char * borderLeftColor() const;
    void setBorderLeftColor(const char * borderLeftColor);

    const char * borderTopStyle() const;
    void setBorderTopStyle(const char * borderTopStyle);

    const char * borderRightStyle() const;
    void setBorderRightStyle(const char * borderRightStyle);

    const char * borderBottomStyle() const;
    void setBorderBottomStyle(const char * borderBottomStyle);

    const char * borderLeftStyle() const;
    void setBorderLeftStyle(const char * borderLeftStyle);

    const char * borderTopWidth() const;
    void setBorderTopWidth(const char * borderTopWidth);

    const char * borderRightWidth() const;
    void setBorderRightWidth(const char * borderRightWidth);

    const char * borderBottomWidth() const;
    void setBorderBottomWidth(const char * borderBottomWidth);

    const char * borderLeftWidth() const;
    void setBorderLeftWidth(const char * borderLeftWidth);

    const char * borderWidth() const;
    void setBorderWidth(const char * borderWidth);

    const char * bottom() const;
    void setBottom(const char * bottom);

    const char * captionSide() const;
    void setCaptionSide(const char * captionSide);

    const char * clear() const;
    void setClear(const char * clear);

    const char * clip() const;
    void setClip(const char * clip);

    const char * color() const;
    void setColor(const char * color);

    const char * content() const;
    void setContent(const char * content);

  protected:
    cssom::CSSStyleDeclaration::Impl _impl;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_DECLARATION_HPP
