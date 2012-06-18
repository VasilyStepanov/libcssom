#ifndef _CSSOM_CSS_PROPERTY_VALUE_BACKGROUND_H
#define _CSSOM_CSS_PROPERTY_VALUE_BACKGROUND_H

#include "CSSPropertyValue_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



extern const CSSOM_CSSPropertyType CSSOM_CSSPropertyValue_backgroundSubtypes[5];

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundAttachment(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundColor(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundImage(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundRepeat(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundPosition(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
