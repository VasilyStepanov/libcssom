#ifndef CSSOM_CSSOM_H
#define CSSOM_CSSOM_H

#include <cssom/CSSStyleSheet.h>
#include <cssom/CSSProperty.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM CSSOM;

CSSOM* CSSOM_create(CSSOM_CSSPropertyDef *defs);

void CSSOM_dispose(CSSOM *cssom);

CSSOM_CSSStyleSheet* CSSOM_parse(CSSOM *cssom, const char *cssText);



#ifdef __cplusplus
}
#endif

#endif
