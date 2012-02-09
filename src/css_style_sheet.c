#include <cssom/css_style_sheet.h>

#include <cssom/types.h>

#include <stdlib.h>



struct _CSSOM_CSSStyleSheet {
  CSSOM_CSSRuleList *cssRules;
};



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet_alloc() {
  CSSOM_CSSStyleSheet *styleSheet;

  styleSheet = (CSSOM_CSSStyleSheet*)malloc(sizeof(CSSOM_CSSStyleSheet));
  if (styleSheet == NULL) return NULL;

  styleSheet->cssRules = NULL;

  return styleSheet;
}



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet) {
  CSSOM_CSSRule **it;

  if (styleSheet == NULL) return;

  if (styleSheet->cssRules != NULL)
    for (it = styleSheet->cssRules; *it != NULL; ++it)
      CSSOM_CSSRule_free(*it);
  free(styleSheet->cssRules);
  free(styleSheet);
}



const CSSOM_CSSRuleList* CSSOM_CSSStyleSheet_cssRules(
  const CSSOM_CSSStyleSheet *styleSheet)
{
  return styleSheet->cssRules;
}
