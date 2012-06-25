#ifndef _CSSOM_LEXICAL_UNIT_RANGE_BOTTOM_H
#define _CSSOM_LEXICAL_UNIT_RANGE_BOTTOM_H

#include "LexicalUnitRange_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_bottom(const CSSOM *cssom,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
