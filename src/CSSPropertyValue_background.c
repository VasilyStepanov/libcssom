#include "CSSPropertyValue_background.h"

#include "gcc.h"

#include <string.h>



static SAC_LexicalUnit unit_transparent;
static SAC_LexicalUnit unit_none;
static SAC_LexicalUnit unit_repeat;
static SAC_LexicalUnit unit_scroll;
static SAC_LexicalUnit unit_0pct;



const CSSOM_CSSPropertyType CSSOM_CSSPropertyValue_backgroundSubtypes[] = {
  CSSOM_BACKGROUND_COLOR_PROPERTY,
  CSSOM_BACKGROUND_IMAGE_PROPERTY,
  CSSOM_BACKGROUND_REPEAT_PROPERTY,
  CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
  CSSOM_BACKGROUND_POSITION_PROPERTY
};



void CSSOM_CSSPropertyValue__initBackgroundGlobals(void) {
  unit_transparent.lexicalUnitType = SAC_IDENT;
  unit_transparent.desc.ident = "transparent";

  unit_none.lexicalUnitType = SAC_IDENT;
  unit_none.desc.ident = "none";

  unit_repeat.lexicalUnitType = SAC_IDENT;
  unit_repeat.desc.ident = "repeat";

  unit_scroll.lexicalUnitType = SAC_IDENT;
  unit_scroll.desc.ident = "scroll";

  unit_0pct.lexicalUnitType = SAC_PERCENTAGE;
  unit_0pct.desc.dimension.unit = "%";
  unit_0pct.desc.dimension.value.sreal = 0;
}



/**
 * background
 */

const SAC_LexicalUnit** CSSOM_LexicalUnitRange_background(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end, 
  struct _CSSOM_LexicalUnitRange *values)
{
  static const SAC_LexicalUnit *color[] = {
    &unit_transparent
  };

  static const SAC_LexicalUnit *image[] = {
    &unit_none
  };

  static const SAC_LexicalUnit *repeat[] = {
    &unit_repeat
  };

  static const SAC_LexicalUnit *attachment[] = {
    &unit_scroll
  };

  static const SAC_LexicalUnit *position[] = {
    &unit_0pct, &unit_0pct
  };

  static const struct _CSSOM_LexicalUnitRange
  initial[_CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes)] = {
    { CSSOM_BACKGROUND_COLOR_PROPERTY, _CSSOM_INITIAL(color) },
    { CSSOM_BACKGROUND_IMAGE_PROPERTY, _CSSOM_INITIAL(image) },
    { CSSOM_BACKGROUND_REPEAT_PROPERTY, _CSSOM_INITIAL(repeat) },
    { CSSOM_BACKGROUND_ATTACHMENT_PROPERTY, _CSSOM_INITIAL(attachment) },
    { CSSOM_BACKGROUND_POSITION_PROPERTY, _CSSOM_INITIAL(position) }
  };

  if (CSSOM_LexicalUnitRange_genericShorthand(initial, &values[1],
    _CSSOM_ASIZE(CSSOM_CSSPropertyValue_backgroundSubtypes), begin, end) != end)
  {
    return begin;
  }

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_PROPERTY, begin, end);
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
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundAttachment(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_ATTACHMENT_PROPERTY,
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
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundColor(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_COLOR_PROPERTY, begin, tail);
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
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundImage(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_IMAGE_PROPERTY, begin, tail);
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
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundRepeat(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_REPEAT_PROPERTY, begin, tail);
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
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  const SAC_LexicalUnit **tail;

  tail = backgroundPosition(begin, end);
  if (tail == begin) return begin;

  _CSSOM_SET_RANGE(values[0], CSSOM_BACKGROUND_POSITION_PROPERTY, begin, tail);
  return tail;
}
