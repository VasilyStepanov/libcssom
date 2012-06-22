#ifndef _CSSOM_CSS_PROPERTY_DATA_H
#define _CSSOM_CSS_PROPERTY_DATA_H

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSPropertyData CSSOM_CSSPropertyData;

CSSOM_CSSPropertyData* CSSOM_CSSPropertyData__alloc(
  const SAC_LexicalUnit *value);

void CSSOM_CSSPropertyData_acquire(CSSOM_CSSPropertyData *data);

void CSSOM_CSSPropertyData_release(CSSOM_CSSPropertyData *data);

const SAC_LexicalUnit** CSSOM_CSSPropertyData_begin(
  const CSSOM_CSSPropertyData *data);

const SAC_LexicalUnit** CSSOM_CSSPropertyData_end(
  const CSSOM_CSSPropertyData *data);

void CSSOM_CSSPropertyData__keepParser(CSSOM_CSSPropertyData *data,
  SAC_Parser parser);



#ifdef __cplusplus
}
#endif

#endif
