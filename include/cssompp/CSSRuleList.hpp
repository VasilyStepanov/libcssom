#ifndef CSSOMPP_CSSRULELIST_HPP
#define CSSOMPP_CSSRULELIST_HPP

#include <cssom/CSSRuleList.h>

namespace cssom{



class CSSStyleSheet;



} // cssom

namespace cssom {



class CSSRuleList {
  public:
    CSSRuleList(const cssom::CSSRuleList &copy);
    ~CSSRuleList();

    cssom::CSSRuleList& operator=(const cssom::CSSRuleList &rhs);

    void swap(cssom::CSSRuleList &rhs);

  private:
    friend class CSSStyleSheet;

    CSSOM_CSSRuleList *_impl;

    explicit CSSRuleList(CSSOM_CSSRuleList *impl);
};



} // cssom

#endif // CSSOMPP_CSSRULELIST_HPP
