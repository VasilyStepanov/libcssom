#ifndef CSSOMPP_SELECTOR_HPP
#define CSSOMPP_SELECTOR_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'Selector.idl'
 */



#include <cssom/typedefs.h>

namespace cssom {



class CSSRule;



} // cssom

namespace cssom {



class Selector {
  public:
    typedef CSSOM_Selector * C;

    Selector();
    explicit Selector(CSSOM_Selector * impl);
    Selector(const cssom::Selector &copy);
    ~Selector();

    cssom::Selector& operator=(const cssom::Selector &rhs);

    bool operator==(const cssom::Selector &rhs) const;

    bool isNull() const;

    void swap(cssom::Selector &rhs);

    const char * selectorText() const;
    void setSelectorText(const char * selectorText);

    cssom::CSSRule parentRule() const;

  protected:
    CSSOM_Selector * _impl;
};



} // cssom

#endif // CSSOMPP_SELECTOR_HPP
