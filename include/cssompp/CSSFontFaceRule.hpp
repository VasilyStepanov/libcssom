#ifndef CSSOMPP_CSS_FONT_FACE_RULE_HPP
#define CSSOMPP_CSS_FONT_FACE_RULE_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssompp/CSSRule.hpp>

#include <cssom/typedefs.h>

namespace cssom {



class CSSStyleDeclaration;



} // cssom

namespace cssom {



class CSSFontFaceRule : public cssom::CSSRule {
  public:
    typedef CSSOM_CSSFontFaceRule * C;

    static cssom::CSSFontFaceRule cast(const cssom::CSSRule & cssRule);
    static cssom::CSSFontFaceRule & cast(cssom::CSSRule & cssRule);

    CSSFontFaceRule();
    explicit CSSFontFaceRule(CSSOM_CSSFontFaceRule * impl);

    cssom::CSSStyleDeclaration style() const;
};



} // cssom

#endif // CSSOMPP_CSS_FONT_FACE_RULE_HPP