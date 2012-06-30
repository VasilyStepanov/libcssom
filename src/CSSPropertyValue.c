#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "LexicalUnitRange_background.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclarationValue.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



/**
 * The largest one.
 */
#define _CSSOM_RANGES_CAPACITY 13



struct _CSSOM_CSSPropertyValue {
  size_t handles;
  const CSSOM *cssom;
  CSSOM_CSSStyleDeclarationValue *parentValues;
  CSSOM_CSSPropertyValue *shorthand;
  int hash;
  const char *name;
  CSSOM_CSSPropertyData *data;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  SAC_Boolean important;
  char *cssText;
};



static int LexicalUnit_eq(const SAC_LexicalUnit *lhs,
  const SAC_LexicalUnit *rhs)
{
  if (lhs->lexicalUnitType != rhs->lexicalUnitType) return 0;

  switch (lhs->lexicalUnitType) {
    case SAC_OPERATOR_PLUS:
    case SAC_OPERATOR_MINUS:
    case SAC_OPERATOR_COMMA:
    case SAC_OPERATOR_SLASH:
    case SAC_OPERATOR_MULTIPLY:
    case SAC_OPERATOR_MOD:
    case SAC_OPERATOR_EXP:
    case SAC_OPERATOR_LT:
    case SAC_OPERATOR_GT:
    case SAC_OPERATOR_LE:
    case SAC_OPERATOR_GE:
    case SAC_OPERATOR_TILDE:
    case SAC_INHERIT:
      break;
    case SAC_INTEGER:
      if (lhs->desc.integer != rhs->desc.integer) return 0;
      break;
    case SAC_REAL:
      if (lhs->desc.real != rhs->desc.real) return 0;
      break;
    case SAC_DIMENSION:
      if (strcmp(lhs->desc.dimension.unit, rhs->desc.dimension.unit) != 0)
        return 0;
      /* no breaks */
    case SAC_LENGTH_EM:
    case SAC_LENGTH_EX:
    case SAC_LENGTH_PIXEL:
    case SAC_LENGTH_INCH:
    case SAC_LENGTH_CENTIMETER:
    case SAC_LENGTH_MILLIMETER:
    case SAC_LENGTH_POINT:
    case SAC_LENGTH_PICA:
    case SAC_PERCENTAGE:
    case SAC_DEGREE:
    case SAC_GRADIAN:
    case SAC_RADIAN:
    case SAC_MILLISECOND:
    case SAC_SECOND:
    case SAC_HERTZ:
    case SAC_KILOHERTZ:
    case SAC_DOTS_PER_INCH:
    case SAC_DOTS_PER_CENTIMETER:
      if (lhs->desc.dimension.value.sreal != rhs->desc.dimension.value.sreal)
        return 0;
      break;
    case SAC_URI:
      if (strcmp(lhs->desc.uri, rhs->desc.uri) != 0) return 0;
      break;
    case SAC_FUNCTION:
      if (strcmp(lhs->desc.function.name, rhs->desc.function.name) < 0)
        return 0;
      /* no breaks */
    case SAC_RGBCOLOR:
    case SAC_ATTR_FUNCTION:
    case SAC_RECT_FUNCTION:
    case SAC_COUNTER_FUNCTION:
    case SAC_COUNTERS_FUNCTION:
    case SAC_NTH_CHILD_FUNCTION:
    case SAC_NTH_LAST_CHILD_FUNCTION:
    case SAC_NTH_OF_TYPE_FUNCTION:
    case SAC_NTH_LAST_OF_TYPE_FUNCTION:
      {
        SAC_LexicalUnit **lhsarg;
        SAC_LexicalUnit **rhsarg;

        for (
          lhsarg = lhs->desc.function.parameters,
          rhsarg = rhs->desc.function.parameters;
          *lhsarg != NULL || *rhsarg != NULL;
          ++lhsarg, ++rhsarg)
        {
          if (*lhsarg == NULL || *rhsarg == NULL) return 0;
          if (LexicalUnit_eq(*lhsarg, *rhsarg) == 0) return 0;
        }
      }
      break;
    case SAC_IDENT:
      if (strcmp(lhs->desc.ident, rhs->desc.ident) != 0) return 0;
      break;
    case SAC_STRING_VALUE:
      if (strcmp(lhs->desc.stringValue, rhs->desc.stringValue) != 0) return 0;
      break;
    case SAC_UNICODERANGE:
      if (strcmp(lhs->desc.unicodeRange, rhs->desc.unicodeRange) != 0) return 0;
      break;
    case SAC_SUB_EXPRESSION:
      {
        SAC_LexicalUnit **lhssub;
        SAC_LexicalUnit **rhssub;

        for (
          lhssub = lhs->desc.subValues,
          rhssub = rhs->desc.subValues;
          *lhssub != NULL || *rhssub != NULL;
          ++lhssub, ++rhssub)
        {
          if (LexicalUnit_eq(*lhssub, *rhssub) == 0) return 0;
        }
      }
      break;
  };
  return 1;
}



static int CSSPropertyValue_eq(const CSSOM_CSSPropertyValue *lhs,
  const CSSOM_CSSPropertyValue *rhs)
{
  const SAC_LexicalUnit **lit;
  const SAC_LexicalUnit **rit;

  if (lhs->end - lhs->begin != rhs->end - rhs->begin) return 0;

  for (lit = lhs->begin, rit = rhs->begin; lit != lhs->end; ++lit, ++rit) {
    if (LexicalUnit_eq(*lit, *rit) == 0) return 0;
  }

  return 1;
}



int LexicalUnitRange_eq(const SAC_LexicalUnit **lhsbegin,
  const SAC_LexicalUnit **lhsend, const SAC_LexicalUnit **rhsbegin,
  const SAC_LexicalUnit **rhsend)
{
  const SAC_LexicalUnit **lit;
  const SAC_LexicalUnit **rit;

  if (lhsend - lhsbegin != rhsend - rhsbegin) return 0;

  for (
    lit = lhsbegin, rit = rhsbegin;
    lit != lhsend;
    ++lit, ++rit)
  {
    if (!LexicalUnit_eq(*lit, *rit)) return 0;
  }

  return 1;
}



static int LexicalUnitRange__emit(const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, FILE *out)
{
  const SAC_LexicalUnit **it;

  it = begin;
  if (it != end) {
    if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    while (++it != end) {
      if (fprintf(out, " ") < 0) return 1;
      if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    }
  }

  return 0;
}



static int CSSPropertyValue_isInherit(const CSSOM_CSSPropertyValue *property) {
  if (property->end - property->begin != 1) return 0;
  return CSSOM_LexicalUnit_isInherit(property->begin[0]);
}



static int testShorthand(const CSSOM_CSSPropertyValue *shorthand, size_t *size,
  int *isInherit)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  size_t _size;
  int _isInherit;
  size_t i;
  CSSOM_CSSPropertyValue *property;

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->hash);
  _size = 0;
  _isInherit = 1;
  for (i = 0; i < setting->nsubhashes; ++i) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, setting->subhashes[i]);

    if (property == NULL) return 0;

    _size += property->end - property->begin;
    if (_isInherit && !CSSPropertyValue_isInherit(property)) _isInherit = 0;
  }

  if (isInherit != NULL) *isInherit = _isInherit;
  if (size != NULL) *size = _size;
  return 1;
}



int CSSOM_CSSPropertyValue__omitGenericShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  size_t i;
  size_t size;
  const CSSOM_CSSPropertyValue *property;
  const SAC_LexicalUnit **rit;
  const SAC_LexicalUnit **wit;
  const SAC_LexicalUnit **holder;
  int rval;
  int isInherit;
  struct _CSSOM_LexicalUnitRange *it;

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->hash);

  if (!testShorthand(shorthand, &size, &isInherit)) return 0;
  if (isInherit) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, setting->subhashes[0]);
    _CSSOM_SET_RANGE(ranges[0], shorthand->hash, property->begin,
      property->end);
  } else {
    holder = (const SAC_LexicalUnit **)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * size);
    if (holder == NULL) return -1;
    wit = holder;
    for (i = 0; i < setting->nsubhashes; ++i) {
      property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
        shorthand->parentValues, setting->subhashes[i]);

      for (rit = property->begin; rit != property->end; ++rit, ++wit)
        *wit = *rit;
    }
    rval = setting->handler(shorthand->cssom, shorthand->parentValues, holder,
      wit, NULL) == wit;
    CSSOM_free(holder);
    if (!rval) return 0;

    it = ranges;
    for (i = 0; i < setting->nsubhashes; ++i) {
      property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
        shorthand->parentValues, setting->subhashes[i]);

      if (LexicalUnitRange_eq(property->begin, property->end,
        setting->initial[i].begin, setting->initial[i].end))
      {
        continue;
      }

      _CSSOM_SET_RANGE(*it, property->hash, property->begin, property->end);
      ++it;
    }

    if (it == ranges) {
      property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
        shorthand->parentValues, setting->subhashes[0]);

      _CSSOM_SET_RANGE(ranges[0], property->hash, property->begin,
        property->end);
    }

  }

  return 0;
}



int CSSOM_CSSPropertyValue__omitBoxShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  CSSOM_CSSPropertyValue *top;
  CSSOM_CSSPropertyValue *right;
  CSSOM_CSSPropertyValue *bottom;
  CSSOM_CSSPropertyValue *left;
  size_t size;
  const SAC_LexicalUnit **rit;
  const SAC_LexicalUnit **wit;
  const SAC_LexicalUnit **holder;
  int rval;
  int topbottom;
  int rightleft;
  int topright;

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->hash);

  top = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subhashes[0]);
  right = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subhashes[1]);
  bottom = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subhashes[2]);
  left = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subhashes[3]);



  /**
   * Imposible shorthand
   */

  if (top == NULL || right == NULL || bottom == NULL || left == NULL) return 0;

  topbottom = CSSPropertyValue_eq(top, bottom);
  rightleft = CSSPropertyValue_eq(right, left);
  topright = CSSPropertyValue_eq(top, right);



  /**
   * Imposible shorthand
   */

  if (!(rightleft && topbottom && topright &&
    CSSPropertyValue_isInherit(top) &&
    CSSPropertyValue_isInherit(right) &&
    CSSPropertyValue_isInherit(bottom) &&
    CSSPropertyValue_isInherit(left)))
  {
    size = 0;
    size += top->end - top->begin;
    size += right->end - right->begin;
    size += bottom->end - bottom->begin;
    size += left->end - left->begin;
    holder = (const SAC_LexicalUnit **)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * size);
    if (holder == NULL) return -1;
    wit = holder;
    for (rit = top->begin; rit != top->end; ++rit, ++wit) *wit = *rit;
    for (rit = right->begin; rit != right->end; ++rit, ++wit) *wit = *rit;
    for (rit = bottom->begin; rit != bottom->end; ++rit, ++wit) *wit = *rit;
    for (rit = left->begin; rit != left->end; ++rit, ++wit) *wit = *rit;
    rval = setting->handler(shorthand->cssom, shorthand->parentValues, holder,
      wit, NULL) == wit;
    CSSOM_free(holder);
    if (!rval) return 0;
  }

  if (rightleft) {
    if (topbottom) {
      if (topright) {
        _CSSOM_SET_RANGE(ranges[0], setting->subhashes[0], top->begin, top->end);
      } else {
        _CSSOM_SET_RANGE(ranges[0], setting->subhashes[0], top->begin, top->end);
        _CSSOM_SET_RANGE(ranges[1], setting->subhashes[1], right->begin,
          right->end);
      }
    } else {
      _CSSOM_SET_RANGE(ranges[0], setting->subhashes[0], top->begin, top->end);
      _CSSOM_SET_RANGE(ranges[1], setting->subhashes[1], right->begin,
        right->end);
      _CSSOM_SET_RANGE(ranges[2], setting->subhashes[2], bottom->begin,
        bottom->end);
    }
  } else {
    _CSSOM_SET_RANGE(ranges[0], setting->subhashes[0], top->begin, top->end);
    _CSSOM_SET_RANGE(ranges[1], setting->subhashes[1], right->begin, right->end);
    _CSSOM_SET_RANGE(ranges[2], setting->subhashes[2], bottom->begin,
      bottom->end);
    _CSSOM_SET_RANGE(ranges[3], setting->subhashes[3], left->begin, left->end);
  }

  return 0;
}



static int fetchRecursiveShorthand(
  const CSSOM *cssom, const CSSOM_CSSStyleDeclarationValue *values,
  const struct _CSSOM_CSSPropertySetting *setting,
  struct _CSSOM_LexicalUnitRange *ranges, size_t *size)
{
  struct _CSSOM_LexicalUnitRange *it;
  const struct _CSSOM_CSSPropertySetting *propertySetting;
  CSSOM_CSSPropertyValue *property;
  size_t nsubhashes;
  size_t i;
  size_t j;
  int rval;

  *size = 0;
  it = ranges;
  for (i = 0; i < setting->nsubhashes; ++i) {
    struct _CSSOM_LexicalUnitRange propertyRanges[_CSSOM_RANGES_CAPACITY] = {
      { 0, NULL, NULL }, /*  0 */
      { 0, NULL, NULL }, /*  1 */
      { 0, NULL, NULL }, /*  2 */
      { 0, NULL, NULL }, /*  3 */
      { 0, NULL, NULL }, /*  4 */
      { 0, NULL, NULL }, /*  5 */
      { 0, NULL, NULL }, /*  6 */
      { 0, NULL, NULL }, /*  7 */
      { 0, NULL, NULL }, /*  8 */
      { 0, NULL, NULL }, /*  9 */
      { 0, NULL, NULL }, /* 10 */
      { 0, NULL, NULL }, /* 11 */
      { 0, NULL, NULL }  /* 12 */
    };

    propertySetting = CSSOM__propertySetting(cssom, setting->subhashes[i]);

    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(values,
      setting->subhashes[i]);

    if (propertySetting->omit != NULL) {
      rval = propertySetting->omit(property, propertyRanges);
      if (rval != 0) return rval;

      nsubhashes = propertySetting->nsubhashes;
    } else {
      if (property == NULL) {
        *size = 0;
        return 0;
      }
      _CSSOM_SET_RANGE(propertyRanges[0], property->hash, property->begin,
        property->end);

      nsubhashes = 1;
    }

    for (j = 0; j < nsubhashes; ++j) {
      if (propertyRanges[j].begin == NULL) break;

      if (j > 1) {
        *size = 0;
        return 0;
      }

      if (LexicalUnitRange_eq(propertyRanges[j].begin, propertyRanges[j].end,
        setting->initial[i].begin, setting->initial[i].end))
      {
        continue;
      }

      *it = propertyRanges[j];
      ++*size;
      ++it;
      assert(*size < _CSSOM_RANGES_CAPACITY);
    }
  }

  return 0;
}



static int applyRecursiveShorthand(const CSSOM *cssom,
  const CSSOM_CSSStyleDeclarationValue *values,
  const struct _CSSOM_CSSPropertySetting *setting,
  const struct _CSSOM_LexicalUnitRange *shorthandRanges, size_t size,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  struct _CSSOM_LexicalUnitRange *it;
  const SAC_LexicalUnit **rit;
  const SAC_LexicalUnit **wit;
  const SAC_LexicalUnit **holder;
  size_t i;
  int rval;
  int isInherit;

  isInherit = size != 0 ? 1 : 0;
  for (i = 0; i < size; ++i) {
    if (shorthandRanges[i].end - shorthandRanges[i].begin != 1) {
      isInherit = 0;
      break;
    }

    if ((**shorthandRanges[i].begin).lexicalUnitType != SAC_INHERIT) {
      isInherit = 0;
      break;
    }
  }

  if (isInherit) {
    _CSSOM_SET_RANGE(ranges[0], shorthandRanges[0].hash,
      shorthandRanges[0].begin, shorthandRanges[0].end);
  } else {
    holder = (const SAC_LexicalUnit **)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * size);
    if (holder == NULL) return -1;
    wit = holder;
    for (i = 0; i < size; ++i) {
      for (
        rit = shorthandRanges[i].begin;
        rit != shorthandRanges[i].end;
        ++rit, ++wit)
      {
        *wit = *rit;
      }
    }
    rval = setting->handler(cssom, values, holder, wit, NULL) == wit;
    CSSOM_free(holder);
    if (!rval) return 0;

    rval = 0;
    it = ranges;
    for (i = 0; i < size; ++i) {
      if (LexicalUnitRange_eq(shorthandRanges[i].begin, shorthandRanges[i].end,
        setting->initial[i].begin, setting->initial[i].end))
      {
        continue;
      }

      _CSSOM_SET_RANGE(*it, shorthandRanges[i].hash, shorthandRanges[i].begin,
        shorthandRanges[i].end);
      ++it;
      rval = 1;
    }

    if (rval == 0)
      _CSSOM_SET_RANGE(ranges[0], setting->initial[0].hash,
        setting->initial[0].begin, setting->initial[0].end);
  }

  return 0;
}



int CSSOM_CSSPropertyValue__omitRecursiveShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *ranges)
{
  struct _CSSOM_LexicalUnitRange _ranges[_CSSOM_RANGES_CAPACITY] = {
    { 0, NULL, NULL }, /*  0 */
    { 0, NULL, NULL }, /*  1 */
    { 0, NULL, NULL }, /*  2 */
    { 0, NULL, NULL }, /*  3 */
    { 0, NULL, NULL }, /*  4 */
    { 0, NULL, NULL }, /*  5 */
    { 0, NULL, NULL }, /*  6 */
    { 0, NULL, NULL }, /*  7 */
    { 0, NULL, NULL }, /*  8 */
    { 0, NULL, NULL }, /*  9 */
    { 0, NULL, NULL }, /* 10 */
    { 0, NULL, NULL }, /* 11 */
    { 0, NULL, NULL }  /* 12 */
  };

  const struct _CSSOM_CSSPropertySetting *setting;
  size_t size;
  int rval;

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->hash);

  rval = fetchRecursiveShorthand(shorthand->cssom, shorthand->parentValues,
    setting, _ranges, &size);
  if (rval != 0) return rval;

  if (size == 0) return 0;

  return applyRecursiveShorthand(shorthand->cssom, shorthand->parentValues,
    setting, _ranges, size, ranges);
}



static int CSSPropertyValue_emit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  struct _CSSOM_LexicalUnitRange ranges[_CSSOM_RANGES_CAPACITY] = {
    { 0, NULL, NULL }, /*  0 */
    { 0, NULL, NULL }, /*  1 */
    { 0, NULL, NULL }, /*  2 */
    { 0, NULL, NULL }, /*  3 */
    { 0, NULL, NULL }, /*  4 */
    { 0, NULL, NULL }, /*  5 */
    { 0, NULL, NULL }, /*  6 */
    { 0, NULL, NULL }, /*  7 */
    { 0, NULL, NULL }, /*  8 */
    { 0, NULL, NULL }, /*  9 */
    { 0, NULL, NULL }, /* 10 */
    { 0, NULL, NULL }, /* 11 */
    { 0, NULL, NULL }  /* 12 */
  };

  const struct _CSSOM_CSSPropertySetting *setting;
  size_t i;
  int rval;
  int emitted;

  setting = CSSOM__propertySetting(property->cssom, property->hash);

  if (setting->omit == NULL)
    return LexicalUnitRange__emit(property->begin, property->end, out);

  rval = setting->omit(property, ranges);
  if (rval != 0) return rval;

  emitted = 0;
  for (i = 0; i < setting->nsubhashes; ++i) {
    if (ranges[i].begin == NULL) break;

    if (emitted) {
      if (fprintf(out, " ") < 0) return -1;
    }

    rval = LexicalUnitRange__emit(ranges[i].begin, ranges[i].end, out);
    if (rval != 0) return rval;

    emitted = 1;
  }

  return 0;
}



static CSSOM_CSSPropertyValue* CSSPropertyValue_alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, int hash, CSSOM_CSSPropertyData *data,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  SAC_Boolean important)
{
  CSSOM_CSSPropertyValue *property;

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) return NULL;

  property->handles = 1;
  property->cssom = cssom;
  property->parentValues = parentValues;
  property->shorthand = shorthand;
  property->hash = hash;
  property->name = CSSOM__propertySetting(cssom, hash)->name;
  property->data = data;
  property->begin = begin;
  property->end = end;
  property->important = important;
  property->cssText = NULL;

  CSSOM_CSSPropertyData_acquire(property->data);

  return property;
}



static CSSOM_CSSPropertyValue* assignProperties(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, CSSOM_CSSPropertyData *data,
  struct _CSSOM_LexicalUnitRange *ranges, size_t size, SAC_Boolean important,
  int *error)
{
  CSSOM_CSSPropertyValue *shorthand;
  CSSOM_CSSPropertyValue *property;
  size_t i;
  int rval;

  if (ranges[0].begin == NULL) {
    if (error != NULL) *error = 1;
    return NULL;
  }

  shorthand = CSSPropertyValue_alloc(cssom, parentValues, NULL, ranges[0].hash,
    data, ranges[0].begin, ranges[0].end, important);
  if (shorthand == NULL) {
    if (error != NULL) *error = -1;
    return NULL;
  }

  for (i = 1; i < size; ++i) {
    if (ranges[i].begin == NULL) continue;

    property = CSSPropertyValue_alloc(cssom, parentValues, shorthand,
      ranges[i].hash, data, ranges[i].begin, ranges[i].end, important);
    if (property == NULL) {
      if (error != NULL) *error = -1;
      return NULL;
    }

    if ((rval = CSSOM_CSSStyleDeclarationValue__assignProperty(parentValues,
      property)) != 0)
    {
      CSSOM_CSSPropertyValue_release(property);
      if (error != NULL) *error = rval;
      return NULL;
    }
  }

  return shorthand;
}



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, int hash,
  CSSOM_CSSPropertyData *data, SAC_Boolean important, int *error)
{
  struct _CSSOM_LexicalUnitRange ranges[_CSSOM_RANGES_CAPACITY] = {
    { 0, NULL, NULL }, /*  0 */
    { 0, NULL, NULL }, /*  1 */
    { 0, NULL, NULL }, /*  2 */
    { 0, NULL, NULL }, /*  3 */
    { 0, NULL, NULL }, /*  4 */
    { 0, NULL, NULL }, /*  5 */
    { 0, NULL, NULL }, /*  6 */
    { 0, NULL, NULL }, /*  7 */
    { 0, NULL, NULL }, /*  8 */
    { 0, NULL, NULL }, /*  9 */
    { 0, NULL, NULL }, /* 10 */
    { 0, NULL, NULL }, /* 11 */
    { 0, NULL, NULL }  /* 12 */
  };

  const struct _CSSOM_CSSPropertySetting *setting;

  CSSOM_CSSPropertyValue *property;

  setting = CSSOM__propertySetting(cssom, hash);

  if (setting->handler(cssom, parentValues, CSSOM_CSSPropertyData_begin(data),
    CSSOM_CSSPropertyData_end(data), ranges) != CSSOM_CSSPropertyData_end(data))
  {
    if (error != NULL) *error = 1;
    return NULL;
  }

  /**
   * FIXME: Drop this line after CSSOM_LexicalUnitRange_whatever cleanup.
   */
  ranges[0].hash = hash;

  property = assignProperties(cssom, parentValues, data, ranges,
    _CSSOM_ARSIZE(ranges), important, error);
  if (property == NULL) return NULL;
  
  if (error != NULL) *error = 0;
  return property;
}



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__allocShorthand(
  const CSSOM *cssom, CSSOM_CSSStyleDeclarationValue *parentValues,
  int hash)
{
  assert(CSSOM__propertySetting(cssom, hash)->nsubhashes != 0);

  return CSSPropertyValue_alloc(cssom, parentValues, NULL, hash, NULL, NULL,
    NULL, SAC_FALSE);
}



void CSSOM_CSSPropertyValue_acquire(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  ++property->handles;
  CSSOM_CSSStyleDeclarationValue_acquire(property->parentValues);
  CSSOM_CSSPropertyValue_acquire(property->shorthand);
}



void CSSOM_CSSPropertyValue_release(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  assert(property->handles > 0);
  --property->handles;
  if (property->handles > 0) {
    CSSOM_CSSPropertyValue_release(property->shorthand);
    CSSOM_CSSStyleDeclarationValue_release(property->parentValues);
    return;
  }

  CSSOM_native_free(property->cssText);
  CSSOM_CSSPropertyData_release(property->data);
  CSSOM_free(property);
}



const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property)
{
  return property->name;
}



const char* CSSOM_CSSPropertyValue_cssText(
  const CSSOM_CSSPropertyValue *property)
{
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(property->cssText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSPropertyValue_emit(property, out) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_CSSPropertyValue*)property)->cssText = buf;

  return property->cssText;
}



static void CSSPropertyValue_swap(
  CSSOM_CSSPropertyValue *lhs, CSSOM_CSSPropertyValue *rhs)
{
  assert(lhs->cssom == rhs->cssom);
  assert(lhs->parentValues == rhs->parentValues);
  SWAPP(lhs->shorthand, rhs->shorthand);
  SWAPS(lhs->hash, rhs->hash);
  SWAPP(lhs->name, rhs->name);
  SWAPP(lhs->data, rhs->data);
  SWAPP(lhs->begin, rhs->begin);
  SWAPP(lhs->end, rhs->end);
  SWAPS(lhs->important, rhs->important);
  SWAPP(lhs->cssText, rhs->cssText);
}



void CSSOM_CSSPropertyValue_setCSSText(CSSOM_CSSPropertyValue *property,
  const char * cssText)
{
  CSSOM_CSSPropertyValue *newProperty;

  newProperty = CSSOM__parsePropertyValue(property->cssom,
    property->parentValues, property->hash, cssText, strlen(cssText), NULL, 0);
  if (newProperty == NULL) return;

  CSSPropertyValue_swap(property, newProperty);

  CSSOM_CSSPropertyValue_release(newProperty);
}



int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property) {
  return property->important == SAC_TRUE ? 1 : 0;
}
