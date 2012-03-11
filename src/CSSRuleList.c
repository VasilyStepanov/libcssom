#include "CSSRuleList.h"

#include <stdlib.h>



CSSOM_CSSRuleList* CSSOM_CSSRuleList__realloc(CSSOM_CSSRuleList *cssRules,
  CSSOM_List_CSSRule *list)
{
  size_t size;
  CSSOM_ListIter_CSSRule lit;
  CSSOM_CSSRuleList *vit;

  size = CSSOM_List_CSSRule_size(list);

  cssRules = (CSSOM_CSSRuleList*)realloc(cssRules,
    sizeof(CSSOM_CSSRuleList) * (size + 1));
  if (cssRules == NULL) return NULL;

  for (lit = CSSOM_List_CSSRule_begin(list), vit = cssRules;
    lit != CSSOM_List_CSSRule_end(list);
    lit = CSSOM_ListIter_CSSRule_next(lit), ++vit)
  {
    *vit = *lit;
  }
  cssRules[size] = NULL;

  return cssRules;
}



void CSSOM_CSSRuleList__free(CSSOM_CSSRuleList *cssRules) {
  free(cssRules);
}
