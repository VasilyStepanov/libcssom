#ifndef CSSOMPP_CSS_RULE_HPP
#define CSSOMPP_CSS_RULE_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/typedefs.h>

namespace cssom {



class CSSStyleSheet;



} // cssom

namespace cssom {



class CSSRule {
  public:
    typedef CSSOM_CSSRule * C;

    CSSRule();
    explicit CSSRule(CSSOM_CSSRule * impl);
    CSSRule(const cssom::CSSRule &copy);
    ~CSSRule();

    cssom::CSSRule& operator=(const cssom::CSSRule &rhs);

    bool operator==(const cssom::CSSRule &rhs) const;

    bool isNull() const;

    void swap(cssom::CSSRule &rhs);

    static unsigned short STYLE_RULE;

    static unsigned short IMPORT_RULE;

    static unsigned short MEDIA_RULE;

    static unsigned short FONT_FACE_RULE;

    static unsigned short PAGE_RULE;

    static unsigned short NAMESPACE_RULE;

    unsigned short type() const;

    const char * cssText() const;
    void setCSSText(const char * cssText);

    cssom::CSSStyleSheet parentStyleSheet() const;

  protected:
    CSSOM_CSSRule * _impl;
};



} // cssom

#endif // CSSOMPP_CSS_RULE_HPP
