#ifndef _CSSOM_CSS_PROPERTY_VALUE_AZIMUTH_H
#define _CSSOM_CSS_PROPERTY_VALUE_AZIMUTH_H

#include "CSSPropertyValue_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_azimuth(const CSSOM *cssom,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
