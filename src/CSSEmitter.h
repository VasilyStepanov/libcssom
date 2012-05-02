#ifndef CSSOM_CSSEMITTER_H
#define CSSOM_CSSEMITTER_H

#include "MediaQuery.h"

#include <cssom/typedefs.h>

#include <sacc.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



int CSSOM_CSSEmitter_lexicalUnit(FILE *out, const SAC_LexicalUnit *value);

int CSSOM_CSSEmitter_property(FILE *out,
  const CSSOM_CSSPropertyValue *property);

int CSSOM_CSSEmitter_selectors(FILE *out, const SAC_Selector *selectors[]);

int CSSOM_CSSEmitter_pageSelectors(FILE *out, const SAC_Selector *selectors[]);

int CSSOM_CSSEmitter_media(FILE *out, const CSSOM_MediaList *media);

int CSSOM_CSSEmitter_query(FILE *out, const CSSOM_MediaQuery *query);

int CSSOM_CSSEmitter_cssStyleDeclaration(FILE *out,
  const CSSOM_CSSStyleDeclaration *style);

int CSSOM_CSSEmitter_cssRule(FILE *out, const CSSOM_CSSRule *cssRule);

int CSSOM_CSSEmitter_cssRules(FILE *out, const CSSOM_CSSRuleList *cssRules);

int CSSOM_CSSEmitter_cssFontFaceRule(FILE *out,
  const CSSOM_CSSFontFaceRule *cssRule);

int CSSOM_CSSEmitter_cssImportRule(FILE *out,
  const CSSOM_CSSImportRule *cssRule);

int CSSOM_CSSEmitter_cssMediaRule(FILE *out, const CSSOM_CSSMediaRule *cssRule);

int CSSOM_CSSEmitter_cssNamespaceRule(FILE *out,
  const CSSOM_CSSNamespaceRule *cssRule);

int CSSOM_CSSEmitter_cssPageRule(FILE *out, const CSSOM_CSSPageRule *cssRule);

int CSSOM_CSSEmitter_cssStyleRule(FILE *out, const CSSOM_CSSStyleRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
