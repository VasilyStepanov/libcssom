#ifndef CSSOMPP_SELECTOR_HPP
#define CSSOMPP_SELECTOR_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/typedefs.h>

namespace cssom {



class CSSRule;



} // cssom

namespace cssom {



class Selector {
  public:
    typedef CSSOM_Selector * Impl;

    Selector();
    explicit Selector(cssom::Selector::Impl impl);
    Selector(const cssom::Selector &copy);
    ~Selector();

    cssom::Selector& operator=(const cssom::Selector &rhs);

    bool operator==(const cssom::Selector &rhs) const;

    bool isNull() const;

    void swap(cssom::Selector &rhs);

    const char * selectorText() const;
    void setSelectorText(const char * selectorText);

    cssom::CSSRule parentRule() const;

    unsigned long specificity() const;

    void select(void * root, void * selection);

  protected:
    cssom::Selector::Impl _impl;
};



} // cssom

#endif // CSSOMPP_SELECTOR_HPP
