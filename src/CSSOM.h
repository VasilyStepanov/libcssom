#ifndef _CSSOM_CSSOM_H
#define _CSSOM_CSSOM_H

#include <cssom/CSSOM.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_acquire(CSSOM *cssom);

void CSSOM_release(CSSOM *cssom);

CSSOM_CSSRule * CSSOM__parseCSSRule(const CSSOM *cssom,
  const char * cssText, int len);



#ifdef __cplusplus
}
#endif

#endif
