#ifndef CSSOMPP_CSS_STYLE_RULE_HPP
#define CSSOMPP_CSS_STYLE_RULE_HPP

#include <cssompp/CSSRule.hpp>

#include <cssom/CSSStyleRule.h>

namespace cssom {



class CSSStyleDeclaration;



} // cssom

namespace cssom {



class CSSStyleRule : public cssom::CSSRule {
  public:
    typedef CSSOM_CSSStyleRule * C;


    const char * selectorText() const;

    cssom::CSSStyleDeclaration style() const;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_RULE_HPP
