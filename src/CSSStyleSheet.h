#ifndef _CSSOM_CSSSTYLESHEET_H
#define _CSSOM_CSSSTYLESHEET_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_CSSStyleSheet* CSSOM_CSSStyleSheet__alloc(const CSSOM *cssom,
  SAC_Parser parser);

const CSSOM* CSSOM_CSSStyleSheet__cssom(const CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
