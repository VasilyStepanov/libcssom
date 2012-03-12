#ifndef CSSOM_CSSRULELIST_H
#define CSSOM_CSSRULELIST_H

#include <cssom/CSSRule.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSRuleList CSSOM_CSSRuleList;



size_t CSSOM_CSSRuleList_size(const CSSOM_CSSRuleList *cssRules);

CSSOM_CSSRule* CSSOM_CSSRuleList_at(const CSSOM_CSSRuleList *cssRules,
  size_t index);



#ifdef __cplusplus
}
#endif

#endif
