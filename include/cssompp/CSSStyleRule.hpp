#ifndef CSSOMPP_CSS_STYLE_RULE_HPP
#define CSSOMPP_CSS_STYLE_RULE_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssompp/CSSRule.hpp>

#include <cssom/typedefs.h>

namespace cssom {



class CSSStyleDeclaration;



class Selector;



} // cssom

namespace cssom {



class CSSStyleRule : public cssom::CSSRule {
  public:
    typedef CSSOM_CSSStyleRule * Impl;

    static cssom::CSSStyleRule cast(const cssom::CSSRule & cssRule);
    static cssom::CSSStyleRule & cast(cssom::CSSRule & cssRule);

    CSSStyleRule();
    explicit CSSStyleRule(cssom::CSSStyleRule::Impl impl);

    cssom::Selector selector() const;

    const char * selectorText() const;
    void setSelectorText(const char * selectorText);

    cssom::CSSStyleDeclaration style() const;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_RULE_HPP
