#ifndef _CSSOM_LEXICAL_UNIT_RANGE_BORDER_H
#define _CSSOM_LEXICAL_UNIT_RANGE_BORDER_H

#include "LexicalUnitRange_utility.h"

#include <sacc.h>

#ifdef __cplusplus
extern "C" {
#endif



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_border(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderCollapse(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderSpacing(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTop(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRight(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottom(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeft(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftColor(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftStyle(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderTopWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderRightWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderBottomWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderLeftWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_borderWidth(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values);



#ifdef __cplusplus
}
#endif

#endif
