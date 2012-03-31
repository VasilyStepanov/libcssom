#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include <cssom/CSSRuleList.h>

#include "CSSRule.h"
#include "Sequence.h"

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSRuleList__alloc() \
  CSSOM_Sequence__alloc(CSSOM_CSSRule__release);



#ifdef __cplusplus
}
#endif

#endif
