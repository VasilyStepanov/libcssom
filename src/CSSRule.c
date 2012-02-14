#include "CSSRule.h"
#include <cssom/CSSRule.h>

#include <stdlib.h>



struct _CSSOM_CSSRule {
  CSSOM_CSSRuleType type;
};



CSSOM_CSSRule* CSSOM_CSSRule_alloc(CSSOM_CSSRuleType type) {
  CSSOM_CSSRule *rule;

  rule = (CSSOM_CSSRule*)malloc(sizeof(CSSOM_CSSRule));
  if (rule == NULL) return NULL;

  rule->type = type;

  return rule;
}



void CSSOM_CSSRule_free(CSSOM_CSSRule *cssRule) {
  free(cssRule);
}



CSSOM_CSSRuleType CSSOM_CSSRule_type(const CSSOM_CSSRule *rule) {
  return rule->type;
}
