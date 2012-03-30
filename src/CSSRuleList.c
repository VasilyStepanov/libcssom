#include "CSSRuleList.h"

#include "CSSRule.h"
#include "Sequence.h"



CSSOM_CSSRuleList* CSSOM_CSSRuleList__alloc() {
  return CSSOM_Sequence__alloc(CSSOM_CSSRule__release);
}
