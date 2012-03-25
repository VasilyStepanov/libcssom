#ifndef CSSOM_CSSEMITTER_H
#define CSSOM_CSSEMITTER_H

#include <cssom/CSSProperty.h>

#include <sacc.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



int CSSOM_CSSEmitter_lexicalUnit(FILE *out, const SAC_LexicalUnit *value);

int CSSOM_CSSEmitter_cssProperty(FILE *out, const CSSOM_CSSProperty *property);

int CSSOM_CSSEmitter_selectors(FILE *out, const SAC_Selector *selectors[]);



#ifdef __cplusplus
}
#endif

#endif