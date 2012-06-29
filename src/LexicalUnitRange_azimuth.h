#ifndef _CSSOM_LEXICAL_UNIT_RANGE_AZIMUTH_H
#define _CSSOM_LEXICAL_UNIT_RANGE_AZIMUTH_H

#include "LexicalUnitRange_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_azimuth(const CSSOM *cssom,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges);



#ifdef __cplusplus
}
#endif

#endif
