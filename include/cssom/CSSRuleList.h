#ifndef CSSOM_CSSRULELIST_H
#define CSSOM_CSSRULELIST_H

#include <cssom/CSSRule.h>
#include <cssom/Sequence.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef CSSOM_Sequence CSSOM_CSSRuleList;



#define CSSOM_CSSRuleList_size(cssRules) \
  CSSOM_Sequence_size((cssRules))

#define CSSOM_CSSRuleList_at(cssRules, index) \
  (CSSOM_CSSRule*)CSSOM_Sequence_at((cssRules), (index))



#ifdef __cplusplus
}
#endif

#endif
