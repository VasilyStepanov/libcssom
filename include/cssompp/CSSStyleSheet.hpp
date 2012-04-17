#ifndef CSSOMPP_CSS_STYLE_SHEET_HPP
#define CSSOMPP_CSS_STYLE_SHEET_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleSheet.idl'
 */



#include <cssompp/CSSRuleList.hpp>

#include <cssom/typedefs.h>


namespace cssom {



class CSSStyleSheet {
  public:
    typedef CSSOM_CSSStyleSheet * C;

    CSSStyleSheet();
    explicit CSSStyleSheet(CSSOM_CSSStyleSheet * impl);
    CSSStyleSheet(const cssom::CSSStyleSheet &copy);
    ~CSSStyleSheet();

    cssom::CSSStyleSheet& operator=(
     const cssom::CSSStyleSheet &rhs);

    bool operator==(
     const cssom::CSSStyleSheet &rhs) const;

    void swap(cssom::CSSStyleSheet &rhs);

    cssom::CSSRuleList cssRules() const;

    unsigned long insertRule(const char * rule, unsigned long index);

    void deleteRule(unsigned long index);

  protected:
    CSSOM_CSSStyleSheet * _impl;
};



} // cssom

#endif // CSSOMPP_CSS_STYLE_SHEET_HPP
