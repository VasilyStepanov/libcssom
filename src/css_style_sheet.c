#include <cssom/css_style_sheet.h>

#include <stdlib.h>



struct _CSSOM_CSSStyleSheet {
  CSSOM_CSSRuleList *cssRules;
};



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
