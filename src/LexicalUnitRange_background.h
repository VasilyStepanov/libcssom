#ifndef _CSSOM_LEXICAL_UNIT_RANGE_BACKGROUND_H
#define _CSSOM_LEXICAL_UNIT_RANGE_BACKGROUND_H

#include "LexicalUnitRange_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundAttachment(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundImage(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundRepeat(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundPosition(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_background(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges);



#ifdef __cplusplus
}
#endif

#endif
