#include <cssom/css_rule_list.h>

#include <stdlib.h>



void CSSOM_CSSRuleList_free(CSSOM_CSSRuleList *cssRules) {
  free(cssRules);
}
