#include "CSSPropertyValue_utility.h"

#include <string.h>



int CSSOM_LexicalUnit_isInherit(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_INHERIT) return 1; 
  return 0;
}



int CSSOM_LexicalUnit_isAngle(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_DEGREE) {
    return 1;
  } else if (value->lexicalUnitType == SAC_GRADIAN) {
    return 1;
  } else if (value->lexicalUnitType == SAC_RADIAN) {
    return 1;
  }
  return 0;
}



int CSSOM_LexicalUnit_isLength(const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
      return 1;
    case SAC_REAL:
      if (value->desc.real == 0) return 1;
      break;
    case SAC_INTEGER:
      if (value->desc.integer == 0) return 1;
      break;
    default:
      break;
  }
  return 0;
}



int CSSOM_LexicalUnit_isNonNegativeLength(const SAC_LexicalUnit *value) {
  switch (value->lexicalUnitType) {
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
      if (value->desc.dimension.value.sreal >= 0) return 1;
      break;
    case SAC_REAL:
      if (value->desc.real == 0) return 1;
      break;
    case SAC_INTEGER:
      if (value->desc.integer == 0) return 1;
      break;
    default:
      break;
  }
  return 0;
}



int CSSOM_LexicalUnit_isColor(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_RGBCOLOR) {
    const SAC_LexicalUnit *red;
    const SAC_LexicalUnit *green;
    const SAC_LexicalUnit *blue;

    if (value->desc.function.parameters[0] == NULL) return 0;
    red = value->desc.function.parameters[0];


    if (red->lexicalUnitType != SAC_INTEGER) return 0;
    if (red->desc.integer < 0 || red->desc.integer > 255) return 0;

    if (value->desc.function.parameters[1] == NULL) return 0;
    if (value->desc.function.parameters[1]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[2] == NULL) return 0;
    green = value->desc.function.parameters[2];

    if (green->lexicalUnitType != SAC_INTEGER) return 0;
    if (green->desc.integer < 0 || green->desc.integer > 255) return 0;

    if (value->desc.function.parameters[3] == NULL) return 0;
    if (value->desc.function.parameters[3]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[4] == NULL) return 0;
    blue = value->desc.function.parameters[4];

    if (blue->lexicalUnitType != SAC_INTEGER) return 0;
    if (blue->desc.integer < 0 || blue->desc.integer > 255) return 0;

    if (value->desc.function.parameters[5] != NULL) return 0;

    return 1;
  } else if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("aqua", value->desc.ident) == 0) return 1;
    if (strcmp("black", value->desc.ident) == 0) return 1;
    if (strcmp("blue", value->desc.ident) == 0) return 1;
    if (strcmp("fuchsia", value->desc.ident) == 0) return 1;
    if (strcmp("gray", value->desc.ident) == 0) return 1;
    if (strcmp("green", value->desc.ident) == 0) return 1;
    if (strcmp("lime", value->desc.ident) == 0) return 1;
    if (strcmp("maroon", value->desc.ident) == 0) return 1;
    if (strcmp("navy", value->desc.ident) == 0) return 1;
    if (strcmp("olive", value->desc.ident) == 0) return 1;
    if (strcmp("orange", value->desc.ident) == 0) return 1;
    if (strcmp("purple", value->desc.ident) == 0) return 1;
    if (strcmp("red", value->desc.ident) == 0) return 1;
    if (strcmp("silver", value->desc.ident) == 0) return 1;
    if (strcmp("teal", value->desc.ident) == 0) return 1;
    if (strcmp("white", value->desc.ident) == 0) return 1;
    if (strcmp("yellow", value->desc.ident) == 0) return 1;
  }
  return 0;
}



int CSSOM_LexicalUnit_isUrl(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_URI) return 1;
  return 0;
}



int CSSOM_LexicalUnit_isPercentage(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_PERCENTAGE) return 1;
  return 0;
}



static const SAC_LexicalUnit** LexicalUnitRange_walk(
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (begin == end) return end;

  for (i = 0; i < size; ++i) {
    if (values[i].begin != NULL) continue;

    tail = CSSOM_propertySettings[initial[i].type].handler(begin, end,
      &values[i]);
    if (tail == begin) continue;

    if (LexicalUnitRange_walk(initial, values, size, tail, end) == end)
      return end;

    values[i].type = 0;
    values[i].begin = NULL;
    values[i].end = NULL;
  }

  return begin;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_genericShorthand(
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *values, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (&begin[1] == end && CSSOM_LexicalUnit_isInherit(begin[0])) {

    for (i = 0; i < size; ++i)
      _CSSOM_SET_RANGE(values, i, initial[i].type, begin, end);

  } else {

    tail = LexicalUnitRange_walk(initial, values, size, begin, end);
    if (tail != end) return begin;

    for (i = 0; i < size; ++i) {
      if (values[i].begin != NULL) continue;

      values[i] = initial[i];
    }

  }

  return end;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_boxShorthand(
  const CSSOM_CSSPropertyType *types, _CSSOM_PropertyHandler handler,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  struct _CSSOM_LexicalUnitRange value;
  switch (end - begin) {
    case 1:
      if (!CSSOM_LexicalUnit_isInherit(begin[0]) && handler(begin, end,
        &value) != end)
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values, 0, types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 1, types[1], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 2, types[2], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 3, types[3], &begin[0], &begin[1]);

      break;
    case 2:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values, 0, types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 1, types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values, 2, types[2], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 3, types[3], &begin[1], &begin[2]);

      break;
    case 3:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values, 0, types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 1, types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values, 2, types[2], &begin[2], &begin[3]);
      _CSSOM_SET_RANGE(values, 3, types[3], &begin[1], &begin[2]);

      break;
    case 4:
      if (handler(&begin[0], &begin[1], &value) != &begin[1] ||
        handler(&begin[1], &begin[2], &value) != &begin[2] ||
        handler(&begin[2], &begin[3], &value) != &begin[3] ||
        handler(&begin[3], &begin[4], &value) != &begin[4])
      {
        return begin;
      }

      _CSSOM_SET_RANGE(values, 0, types[0], &begin[0], &begin[1]);
      _CSSOM_SET_RANGE(values, 1, types[1], &begin[1], &begin[2]);
      _CSSOM_SET_RANGE(values, 2, types[2], &begin[2], &begin[3]);
      _CSSOM_SET_RANGE(values, 3, types[3], &begin[3], &begin[4]);

      break;
  }

  return end;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_whatever(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values)
{
  _CSSOM_SET_RANGE(values, 0, 0, begin, end);
  return end;
}
