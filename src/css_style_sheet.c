#include "css_style_sheet.h"
#include <cssom/css_style_sheet.h>

#include "css_rule_list.h"

#include <cssom/types.h>

#include <stdlib.h>



struct _CSSOM_CSSStyleSheet {
  CSSOM_CSSRuleList *cssRules;
};



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_alloc(CSSOM_List_CSSRule *list) {
  CSSOM_CSSRuleList *cssRules;
  CSSOM_CSSStyleSheet *styleSheet;

  cssRules = CSSOM_CSSRuleList_alloc(list);
  if (cssRules == NULL) return NULL;
  
  styleSheet = (CSSOM_CSSStyleSheet*)malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) {
    free(cssRules);
    return NULL;
  }

  styleSheet->cssRules = cssRules;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet) {
  if (styleSheet == NULL) return;

  CSSOM_CSSRuleList_free(styleSheet->cssRules);
  free(styleSheet);
}



const CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->cssRules;
}
