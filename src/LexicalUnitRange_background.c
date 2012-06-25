#include "LexicalUnitRange_background.h"

#include "CSSOM.h"
#include "gcc.h"

#include <string.h>
#include <assert.h>



/**
 * background
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_background(
  const CSSOM *cssom, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  static const _CSSOM_PropertyHandler handlers[5] = {
    CSSOM_LexicalUnitRange_backgroundColor,
    CSSOM_LexicalUnitRange_backgroundImage,
    CSSOM_LexicalUnitRange_backgroundRepeat,
    CSSOM_LexicalUnitRange_backgroundAttachment,
    CSSOM_LexicalUnitRange_backgroundPosition
  };

  int marker[5] = { 0, 0, 0, 0, 0 };

  assert(CSSOM__propertySetting(cssom,
    CSSOM_BACKGROUND_PROPERTY)->nsubtypes == _CSSOM_ASIZE(marker));

  assert(CSSOM__propertySetting(cssom,
    CSSOM_BACKGROUND_PROPERTY)->nsubtypes == _CSSOM_ASIZE(handlers));

  if (CSSOM_LexicalUnitRange_genericShorthand(cssom, CSSOM_BACKGROUND_PROPERTY,
    handlers, values != NULL ? &values[1] : NULL, marker, begin, end) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_PROPERTY, begin, end);
  return end;
}



/**
 * background-attachment
 */

static const SAC_LexicalUnit** backgroundAttachment(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("scroll", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("fixed", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundAttachment(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundAttachment(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
    begin, tail);
  return tail;
}



/**
 * background-color
 */

static const SAC_LexicalUnit** backgroundColor(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isColor(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("transparent", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundColor(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_COLOR_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-image
 */

static const SAC_LexicalUnit** backgroundImage(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isUrl(begin[0])) {
    return &begin[1];
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("none", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundImage(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundImage(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_IMAGE_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-repeat
 */

static const SAC_LexicalUnit** backgroundRepeat(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (begin[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("repeat", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("repeat-x", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("repeat-y", begin[0]->desc.ident) == 0) return &begin[1];
    if (strcmp("no-repeat", begin[0]->desc.ident) == 0) return &begin[1];
  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundRepeat(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundRepeat(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_REPEAT_PROPERTY, begin, tail);
  return tail;
}



/**
 * background-position
 */

static const SAC_LexicalUnit** backgroundPosition_horizontal(
  const SAC_LexicalUnit **expr)
{
  if (expr[0] == NULL) {
    return &expr[0];
  } else if (CSSOM_LexicalUnit_isPercentage(expr[0])) {
    return &expr[1];
  } else if (CSSOM_LexicalUnit_isLength(expr[0])) {
    return &expr[1];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("top", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("bottom", expr[0]->desc.ident) == 0) return &expr[1];
  }

  return &expr[0];
}



static const SAC_LexicalUnit** backgroundPosition_vertical(
  const SAC_LexicalUnit **expr)
{
  if (expr[0] == NULL) {
    return &expr[0];
  } else if (expr[0]->lexicalUnitType == SAC_IDENT) {
    if (strcmp("left", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("center", expr[0]->desc.ident) == 0) return &expr[1];
    if (strcmp("right", expr[0]->desc.ident) == 0) return &expr[1];
  }
  return &expr[0];
}



static const SAC_LexicalUnit** backgroundPosition(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end CSSOM_UNUSED)
{
  if (CSSOM_LexicalUnit_isPercentage(begin[0]) ||
    CSSOM_LexicalUnit_isLength(begin[0]))
  {
    return backgroundPosition_horizontal(&begin[1]);
  } else if (begin[0]->lexicalUnitType == SAC_IDENT) {

    if (strcmp("left", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcmp("right", begin[0]->desc.ident) == 0)
      return backgroundPosition_horizontal(&begin[1]);

    if (strcmp("top", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcmp("bottom", begin[0]->desc.ident) == 0)
      return backgroundPosition_vertical(&begin[1]);

    if (strcmp("center", begin[0]->desc.ident) == 0) {
      const SAC_LexicalUnit **tail;

      if (begin[1] == NULL) return &begin[1];

      tail = backgroundPosition_horizontal(&begin[1]);
      if (tail != &begin[1]) return tail;

      return backgroundPosition_vertical(&begin[1]);
    }

  } else if (CSSOM_LexicalUnit_isInherit(begin[0])) {
    return &begin[1];
  }
  return &begin[0];
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_backgroundPosition(
  const CSSOM *cssom CSSOM_UNUSED, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundPosition(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values, 0, CSSOM_BACKGROUND_POSITION_PROPERTY, begin, tail);
  return tail;
}
