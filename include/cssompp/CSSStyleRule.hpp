#ifndef CSSOMPP_CSS_STYLE_RULE_HPP
#define CSSOMPP_CSS_STYLE_RULE_HPP

#include <cssom/CSSStyleRule.h>
#include <cssompp/CSSRule.hpp>

namespace cssom {



class CSSStyleDeclaration;



} // cssom

namespace cssom {



class CSSStyleRule : public cssom::CSSRule {
  public:

    const char * selectorText() const;

    cssom::CSSStyleDeclaration style() const;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_RULE_HPP
