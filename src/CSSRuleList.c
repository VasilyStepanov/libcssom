#include "CSSRuleList.h"

#include "CSSRule.h"

#include <cssom/CSSRule.h>

#include <stdlib.h>



CSSOM_CSSRuleList* CSSOM_CSSRuleList_alloc(CSSOM_List_CSSRule *list) {
  CSSOM_CSSRuleList *cssRules;
  CSSOM_ListIter_CSSRule lit;
  CSSOM_CSSRule **rit;
  size_t size;

  size = CSSOM_List_CSSRule_size(list);
  cssRules = (CSSOM_CSSRuleList*)malloc(sizeof(CSSOM_CSSRule*) * (size + 1));
  if (cssRules == NULL) return NULL;

  for (lit = CSSOM_List_CSSRule_begin(list), rit = cssRules;
    lit != CSSOM_List_CSSRule_end(list);
    lit = CSSOM_ListIter_CSSRule_next(lit), ++rit)
  {
    *rit = *lit;
  }

  cssRules[size] = NULL;

  return cssRules;
}



void CSSOM_CSSRuleList_free(CSSOM_CSSRuleList *cssRules) {
  CSSOM_CSSRule **it;

  for (it = cssRules; *it != NULL; ++it)
    CSSOM_CSSRule_free(*it);
  free(cssRules);
}
