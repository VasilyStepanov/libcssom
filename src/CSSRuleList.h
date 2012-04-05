#ifndef _CSSOM_CSSRULELIST_H
#define _CSSOM_CSSRULELIST_H

#include <cssom/CSSRuleList.h>

#include "CSSRule.h"
#include "Sequence.h"

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSRuleList__alloc() \
  CSSOM_Sequence__alloc((void(*)(void*))CSSOM_CSSRule__free);



#ifdef __cplusplus
}
#endif

#endif
