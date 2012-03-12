#ifndef CSSOMPP_CSSRULE_HPP
#define CSSOMPP_CSSRULE_HPP

#include <cssom/CSSRule.h>

namespace cssom {



class CSSRuleList;
class CSSStyleRule;



} // cssom

namespace cssom {



typedef CSSOM_CSSRuleType CSSRuleType;



class CSSRule {
  public:
    CSSRule(const cssom::CSSRule &copy);
    virtual ~CSSRule();

    CSSRule& operator=(const cssom::CSSRule &rhs);

    void swap(cssom::CSSRule &cssRule);

    cssom::CSSRuleType type() const;

  private:
    friend class CSSRuleList;
    friend class CSSStyleRule;

    CSSOM_CSSRule *_impl;

    explicit CSSRule(CSSOM_CSSRule *impl);
};



} // cssom

#endif // CSSOMPP_CSSRULE_HPP
