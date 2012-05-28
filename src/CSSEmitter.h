#ifndef CSSOM_CSSEMITTER_H
#define CSSOM_CSSEMITTER_H

#include "MediaQuery.h"

#include <cssom/typedefs.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



int CSSOM_CSSEmitter_lexicalUnit(FILE *out, const SAC_LexicalUnit *value);

int CSSOM_CSSEmitter_selector(FILE *out, const CSSOM_Selector *selector);

int CSSOM_CSSEmitter_pageSelector(FILE *out, const CSSOM_Selector *selector);

int CSSOM_CSSEmitter_media(FILE *out, const CSSOM_MediaList *media);

int CSSOM_CSSEmitter_query(FILE *out, const CSSOM_MediaQuery *query);

int CSSOM_CSSEmitter_styleDeclaration(FILE *out,
  const CSSOM_CSSStyleDeclaration *style);

int CSSOM_CSSEmitter_fontFaceRule(FILE *out,
  const CSSOM_CSSFontFaceRule *cssRule);

int CSSOM_CSSEmitter_importRule(FILE *out, const CSSOM_CSSImportRule *cssRule);

int CSSOM_CSSEmitter_mediaRule(FILE *out, const CSSOM_CSSMediaRule *cssRule);

int CSSOM_CSSEmitter_namespaceRule(FILE *out,
  const CSSOM_CSSNamespaceRule *cssRule);

int CSSOM_CSSEmitter_pageRule(FILE *out, const CSSOM_CSSPageRule *cssRule);

int CSSOM_CSSEmitter_styleRule(FILE *out, const CSSOM_CSSStyleRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
