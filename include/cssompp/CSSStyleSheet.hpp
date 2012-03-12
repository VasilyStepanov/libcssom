#ifndef CSSOMPP_CSSSTYLESHEET_HPP
#define CSSOMPP_CSSSTYLESHEET_HPP

#include <cssom/CSSStyleSheet.h>

namespace cssom {



class CSSOM;



} // cssom

namespace cssom {



class CSSStyleSheet {
  public:
    CSSStyleSheet(const cssom::CSSStyleSheet &copy);
    ~CSSStyleSheet();

    cssom::CSSStyleSheet& operator=(const cssom::CSSStyleSheet &rhs);

    void swap(CSSStyleSheet &rhs);

  private:
    friend class cssom::CSSOM;

    CSSOM_CSSStyleSheet *_impl;

    explicit CSSStyleSheet(CSSOM_CSSStyleSheet *impl);
};



} // cssom

#endif // CSSOMPP_CSSSTYLESHEET_HPP
