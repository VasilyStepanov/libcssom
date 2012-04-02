#ifndef CSSOM_CSSOM_H
#define CSSOM_CSSOM_H

#include <cssom/CSSStyleSheet.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM CSSOM;



CSSOM* CSSOM_create(const char **properties);

void CSSOM_dispose(CSSOM *cssom);

CSSOM_CSSStyleSheet* CSSOM_parseStyleSheet(CSSOM *cssom,
  const char *cssText, int len);

void CSSOM_CSSStyleSheet_dispose(CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
