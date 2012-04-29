#ifndef CSSOMPP_CSS_MEDIA_RULE_HPP
#define CSSOMPP_CSS_MEDIA_RULE_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssompp/CSSRuleList.hpp>
#include <cssompp/CSSRule.hpp>

#include <cssom/typedefs.h>

namespace cssom {



class MediaList;



} // cssom

namespace cssom {



class CSSMediaRule : public cssom::CSSRule {
  public:
    typedef CSSOM_CSSMediaRule * C;

    static cssom::CSSMediaRule cast(const cssom::CSSRule & cssRule);
    static cssom::CSSMediaRule & cast(cssom::CSSRule & cssRule);

    CSSMediaRule();
    explicit CSSMediaRule(CSSOM_CSSMediaRule * impl);

    cssom::MediaList media() const;

    void setMedia(const char * media);

    cssom::CSSRuleList cssRules() const;

    unsigned long insertRule(const char * rule, unsigned long index);

    void deleteRule(unsigned long index);
};



} // cssom

#endif // CSSOMPP_CSS_MEDIA_RULE_HPP
