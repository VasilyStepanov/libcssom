#ifndef CSSOMPP_CSSRULELIST_HPP
#define CSSOMPP_CSSRULELIST_HPP

#include <cssompp/CSSRule.hpp>

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

    size_t size() const;
    cssom::CSSRule operator[](size_t index) const;

  private:
    friend class CSSStyleSheet;

    CSSOM_CSSRuleList *_impl;

    explicit CSSRuleList(CSSOM_CSSRuleList *impl);
};



} // cssom

#endif // CSSOMPP_CSSRULELIST_HPP
