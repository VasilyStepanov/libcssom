#include "LexicalUnitRange_utility.h"

#include "CSSOM.h"
#include "gcc.h"

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



int CSSOM_LexicalUnit_isUri(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_URI) return 1;
  return 0;
}



int CSSOM_LexicalUnit_isPercentage(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_PERCENTAGE) return 1;
  return 0;
}



static int LexicalUnit_isShapeArg(const SAC_LexicalUnit *value) {
  if (CSSOM_LexicalUnit_isLength(value)) {
    return 1;
  } else if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("auto", value->desc.ident) == 0) return 1;
  }
  return 0;
}



int CSSOM_LexicalUnit_isShape(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_RECT_FUNCTION) {
    if (value->desc.function.parameters[0] == NULL) return 0;
    if (!LexicalUnit_isShapeArg(value->desc.function.parameters[0]))
      return 0;

    if (value->desc.function.parameters[1] == NULL) return 0;
    if (value->desc.function.parameters[1]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[2] == NULL) return 0;
    if (!LexicalUnit_isShapeArg(value->desc.function.parameters[2]))
      return 0;

    if (value->desc.function.parameters[3] == NULL) return 0;
    if (value->desc.function.parameters[3]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[4] == NULL) return 0;
    if (!LexicalUnit_isShapeArg(value->desc.function.parameters[4]))
      return 0;

    if (value->desc.function.parameters[5] == NULL) return 0;
    if (value->desc.function.parameters[5]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[6] == NULL) return 0;
    if (!LexicalUnit_isShapeArg(value->desc.function.parameters[6]))
      return 0;

    if (value->desc.function.parameters[7] != NULL) return 0;

    return 1;
  }
  return 0;
}



int CSSOM_LexicalUnit_isString(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_STRING_VALUE) return 1;
  return 0;
}



static int LexicalUnit_isListStyleType(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_IDENT) {
    if (strcmp("disc", value->desc.ident) == 0) return 1;
    if (strcmp("circle", value->desc.ident) == 0) return 1;
    if (strcmp("square", value->desc.ident) == 0) return 1;
    if (strcmp("decimal", value->desc.ident) == 0) return 1;
    if (strcmp("decimal-leading-zero", value->desc.ident) == 0) return 1;
    if (strcmp("lower-roman", value->desc.ident) == 0) return 1;
    if (strcmp("upper-roman", value->desc.ident) == 0) return 1;
    if (strcmp("lower-greek", value->desc.ident) == 0) return 1;
    if (strcmp("lower-latin", value->desc.ident) == 0) return 1;
    if (strcmp("upper-latin", value->desc.ident) == 0) return 1;
    if (strcmp("armenian", value->desc.ident) == 0) return 1;
    if (strcmp("georgian", value->desc.ident) == 0) return 1;
    if (strcmp("lower-alpha", value->desc.ident) == 0) return 1;
    if (strcmp("upper-alpha", value->desc.ident) == 0) return 1;
    if (strcmp("none", value->desc.ident) == 0) return 1;
  }
  return 0;
}



int CSSOM_LexicalUnit_isCounter(const SAC_LexicalUnit *value) {
  if (value->lexicalUnitType == SAC_COUNTER_FUNCTION) {
    if (value->desc.function.parameters[0] == NULL) return 0;
    if (value->desc.function.parameters[0]->lexicalUnitType != SAC_IDENT)
      return 0;

    if (value->desc.function.parameters[1] == NULL) return 1;
    if (value->desc.function.parameters[1]->lexicalUnitType !=
      SAC_OPERATOR_COMMA)
    {
      return 0;
    }

    if (value->desc.function.parameters[2] == NULL) return 0;
    if (!LexicalUnit_isListStyleType(value->desc.function.parameters[2]))
      return 0;

    if (value->desc.function.parameters[3] != NULL) return 0;

    return 1;
  }
  return 0;
}



static const SAC_LexicalUnit** LexicalUnitRange_walk(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const int *subhashes, const _CSSOM_PropertyHandler *handlers,
  struct _CSSOM_LexicalUnitRange *ranges, int *marker, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (begin == end) return end;

  for (i = 0; i < size; ++i) {
    if (marker[i]) continue;

    tail = handlers[i](cssom, values, begin, end,
      ranges != NULL ? &ranges[i] : NULL);
    if (tail == begin) continue;

    marker[i] = 1;

    if (LexicalUnitRange_walk(cssom, values, subhashes, handlers, ranges,
      marker, size, tail, end) == end)
    {
      return end;
    }

    marker[i] = 0;
    if (ranges != NULL)
      _CSSOM_SET_RANGE(ranges[i], 0, NULL, NULL);
  }

  return begin;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_genericShorthand(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const int *subhashes, const _CSSOM_PropertyHandler *handlers,
  const struct _CSSOM_LexicalUnitRange *initial,
  struct _CSSOM_LexicalUnitRange *ranges, int *marker, size_t size,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end)
{
  size_t i;
  const SAC_LexicalUnit **tail;

  if (&begin[1] == end && CSSOM_LexicalUnit_isInherit(begin[0])) {

    if (ranges != NULL) {
      for (i = 0; i < size; ++i) {
        _CSSOM_SET_RANGE(ranges[i], subhashes[i], begin, end);
      }
    }

    tail = end;

  } else {

    tail = LexicalUnitRange_walk(cssom, values, subhashes, handlers, ranges,
      marker, size, begin, end);
    if (tail == begin) return begin;
  
    if (ranges != NULL) {
      for (i = 0; i < size; ++i) {
        if (ranges[i].begin != NULL) continue;

        ranges[i] = initial[i];
      }
    }

  }

  return tail;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_boxShorthand(const CSSOM *cssom,
  const CSSOM_CSSStyleDeclarationValue *values, const int *subhashes,
  _CSSOM_PropertyHandler handler, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, struct _CSSOM_LexicalUnitRange *ranges)
{
  switch (end - begin) {
    case 1:
      if (!CSSOM_LexicalUnit_isInherit(begin[0]) && handler(cssom, values,
        begin, end, NULL) != end)
      {
        return begin;
      }

      if (ranges != NULL) {
        _CSSOM_SET_RANGE(ranges[0], subhashes[0], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[1], subhashes[1], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[2], subhashes[2], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[3], subhashes[3], &begin[0], &begin[1]);
      }

      break;
    case 2:
      if (handler(cssom, values, &begin[0], &begin[1], NULL) != &begin[1] ||
        handler(cssom, values, &begin[1], &begin[2], NULL) != &begin[2])
      {
        return begin;
      }

      if (ranges != NULL) {
        _CSSOM_SET_RANGE(ranges[0], subhashes[0], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[1], subhashes[1], &begin[1], &begin[2]);
        _CSSOM_SET_RANGE(ranges[2], subhashes[2], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[3], subhashes[3], &begin[1], &begin[2]);
      }

      break;
    case 3:
      if (handler(cssom, values, &begin[0], &begin[1], NULL) != &begin[1] ||
        handler(cssom, values, &begin[1], &begin[2], NULL) != &begin[2] ||
        handler(cssom, values, &begin[2], &begin[3], NULL) != &begin[3])
      {
        return begin;
      }

      if (ranges != NULL) {
        _CSSOM_SET_RANGE(ranges[0], subhashes[0], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[1], subhashes[1], &begin[1], &begin[2]);
        _CSSOM_SET_RANGE(ranges[2], subhashes[2], &begin[2], &begin[3]);
        _CSSOM_SET_RANGE(ranges[3], subhashes[3], &begin[1], &begin[2]);
      }

      break;
    case 4:
      if (handler(cssom, values, &begin[0], &begin[1], NULL) != &begin[1] ||
        handler(cssom, values, &begin[1], &begin[2], NULL) != &begin[2] ||
        handler(cssom, values, &begin[2], &begin[3], NULL) != &begin[3] ||
        handler(cssom, values, &begin[3], &begin[4], NULL) != &begin[4])
      {
        return begin;
      }

      if (ranges != NULL) {
        _CSSOM_SET_RANGE(ranges[0], subhashes[0], &begin[0], &begin[1]);
        _CSSOM_SET_RANGE(ranges[1], subhashes[1], &begin[1], &begin[2]);
        _CSSOM_SET_RANGE(ranges[2], subhashes[2], &begin[2], &begin[3]);
        _CSSOM_SET_RANGE(ranges[3], subhashes[3], &begin[3], &begin[4]);
      }

      break;
    default:
      return begin;
  }

  return end;
}



const SAC_LexicalUnit** CSSOM_LexicalUnitRange_whatever(
  const CSSOM *cssom CSSOM_UNUSED,
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  if (ranges != NULL)
    _CSSOM_SET_RANGE(ranges[0], 0, begin, end);
  return end;
}
