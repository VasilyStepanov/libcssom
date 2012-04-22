#include "CSSRuleList.h"

#include "CSSFontFaceRule.h"
#include "CSSImportRule.h"
#include "CSSMediaRule.h"
#include "CSSNamespaceRule.h"
#include "CSSPageRule.h"
#include "CSSStyleRule.h"



CSSOM_CSSFontFaceRule* CSSOM_CSSRuleList__appendCSSFontFaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet)
{
  CSSOM_CSSFontFaceRule *cssRule;

  cssRule = CSSOM_CSSFontFaceRule__alloc(parentRule, parentStyleSheet);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSImportRule* CSSOM_CSSRuleList__appendCSSImportRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_STRING base,
  const SAC_STRING uri, const SAC_MediaQuery *media[],
  const SAC_STRING defaultNamepaceURI)
{
  CSSOM_CSSImportRule *cssRule;

  cssRule = CSSOM_CSSImportRule__alloc(parentRule, parentStyleSheet,
    base, uri, media, defaultNamepaceURI);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSMediaRule* CSSOM_CSSRuleList__appendCSSMediaRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_MediaQuery *media[])
{
  CSSOM_CSSMediaRule *cssRule;

  cssRule = CSSOM_CSSMediaRule__alloc(parentRule, parentStyleSheet, media);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSNamespaceRule* CSSOM_CSSRuleList__appendCSSNamespaceRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_STRING prefix,
  const SAC_STRING uri)
{
  CSSOM_CSSNamespaceRule *cssRule;

  cssRule = CSSOM_CSSNamespaceRule__alloc(parentRule, parentStyleSheet,
    prefix, uri);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSPageRule* CSSOM_CSSRuleList__appendCSSPageRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_Selector *selectors[])
{
  CSSOM_CSSPageRule *cssRule;

  cssRule = CSSOM_CSSPageRule__alloc(parentRule, parentStyleSheet, selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



CSSOM_CSSStyleRule* CSSOM_CSSRuleList__appendCSSStyleRule(
  CSSOM_CSSRuleList *cssRules, CSSOM_CSSRule *parentRule,
  CSSOM_CSSStyleSheet *parentStyleSheet, const SAC_Selector *selectors[])
{
  CSSOM_CSSStyleRule *cssRule;

  cssRule = CSSOM_CSSStyleRule__alloc(parentRule, parentStyleSheet, selectors);
  if (cssRule == NULL) return NULL;

  if (CSSOM_Sequence__append(cssRules,
    (CSSOM_CSSRule*)cssRule) == NULL)
  {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)cssRule);
    return NULL;
  }

  return cssRule;
}



struct _CSSOM_HierarchyState {
  int mayStyleRule;
  int mayImportRule;
  int mayMediaRule;
  int mayFontFaceRule;
  int mayPageRule;
  int mayNamespaceRule;
};



static int check(struct _CSSOM_HierarchyState *state, unsigned short type) {
  if (type == CSSOM_CSSRule_STYLE_RULE) {
    if (state->mayStyleRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayImportRule = 0;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 0;
  } else if (type == CSSOM_CSSRule_IMPORT_RULE) {
    if (state->mayImportRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayStyleRule = 1;
    state->mayImportRule = 1;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 1;
  } else if (type == CSSOM_CSSRule_MEDIA_RULE) {
    if (state->mayMediaRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayImportRule = 0;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 0;
  } else if (type == CSSOM_CSSRule_FONT_FACE_RULE) {
    if (state->mayFontFaceRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayImportRule = 0;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 0;
  } else if (type == CSSOM_CSSRule_PAGE_RULE) {
    if (state->mayPageRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayImportRule = 0;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 0;
  } else if (type == CSSOM_CSSRule_NAMESPACE_RULE) {
    if (state->mayNamespaceRule == 0) return 0;
    state->mayStyleRule = 1;
    state->mayImportRule = 0;
    state->mayMediaRule = 1;
    state->mayFontFaceRule = 1;
    state->mayPageRule = 1;
    state->mayNamespaceRule = 1;
  }
  return 1;
}



int CSSOM_CSSRuleList__testHierarchy(const CSSOM_CSSRuleList *cssRules,
  unsigned long index, CSSOM_CSSRule *cssRule)
{
  size_t size;
  size_t i;
  struct _CSSOM_HierarchyState state = {
    1, 1, 1, 1, 1, 1
  };

  size = CSSOM_CSSRuleList_size(cssRules);
  for (i = 0; i < size; ++i) {
    CSSOM_CSSRule *curCSSRule;

    curCSSRule = CSSOM_CSSRuleList_at(cssRules, i);

    if (i == index && !check(&state, CSSOM_CSSRule_type(cssRule))) return 0;
    if (!check(&state, CSSOM_CSSRule_type(curCSSRule))) return 0;
  }

  if (i == index && !check(&state, CSSOM_CSSRule_type(cssRule))) return 0;

  return 1;
}




