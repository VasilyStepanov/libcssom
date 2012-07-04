#ifndef _CSSOM_LEXICAL_UNIT_RANGE_CUE_H
#define _CSSOM_LEXICAL_UNIT_RANGE_CUE_H

#include "LexicalUnitRange_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cueAfter(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cueBefore(const CSSOM *cssom,
  const CSSOM_CSSStyleDeclarationValue *values, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_cue(const CSSOM *cssom,
  const CSSOM_CSSStyleDeclarationValue *values, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);



#ifdef __cplusplus
}
#endif

#endif
