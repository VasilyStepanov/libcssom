#ifndef CSSOMPP_CSSSTYLERULE_HPP
#define CSSOMPP_CSSSTYLERULE_HPP

#include <cssompp/CSSStyleDeclaration.hpp>

#include <cssompp/CSSRule.hpp>

namespace cssom {



class CSSStyleRule : public cssom::CSSRule {
  public:
    const char* selectorText() const;
    cssom::CSSStyleDeclaration style();
};



}

#endif // CSSOMPP_CSSSTYLERULE_HPP
