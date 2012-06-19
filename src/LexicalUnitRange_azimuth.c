#include "LexicalUnitRange_azimuth.h"

#include "gcc.h"

#include <string.h>



static int azimuth_isAngleIdent(const char *ident) {
  if (strcmp("left-side", ident) == 0) return 1;
  if (strcmp("far-left", ident) == 0) return 1;
  if (strcmp("left", ident) == 0) return 1;
  if (strcmp("center-left", ident) == 0) return 1;
  if (strcmp("center", ident) == 0) return 1;
  if (strcmp("center-right", ident) == 0) return 1;
  if (strcmp("right", ident) == 0) return 1;
  if (strcmp("far-right", ident) == 0) return 1;
  if (strcmp("right-side", ident) == 0) return 1;
  return 0;
}



static const SAC_LexicalUnit** azimuth_angle(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (strcmp("behind", begin[0]->desc.ident) == 0) {
        return &begin[1];
      }
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** azimuth_behind(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (begin != end) {
    if (begin[0]->lexicalUnitType == SAC_IDENT) {
      if (azimuth_isAngleIdent(begin[0]->desc.ident)) {
        return &begin[1];
      }
    }
  }
  return &begin[0];
}



static const SAC_LexicalUnit** azimuth(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end)
{
  if (CSSOM_LexicalUnit_isAngle(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("leftwards", begin[0]->desc.ident) == 0) {
      return &begin[1];
    }
    if (strcmp("rightwards", begin[0]->desc.ident) == 0) {
      return &begin[1];
    }

    if (azimuth_isAngleIdent(begin[0]->desc.ident))
      return azimuth_angle(&begin[1], end);

    if (strcmp("behind", begin[0]->desc.ident) == 0)
      return azimuth_behind(&begin[1], end);

  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_azimuth(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = azimuth(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_AZIMUTH_PROPERTY, begin, tail);
  return tail;
}
