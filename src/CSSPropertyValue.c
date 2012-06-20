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



void CSSOM_CSSPropertyValue__initGlobals(void) {
  CSSOM_CSSPropertyValue__initBackgroundGlobals();
}



struct _CSSOM_CSSPropertyValue {
  size_t handles;
  const CSSOM *cssom;
  CSSOM_CSSStyleDeclarationValue *parentValues;
  CSSOM_CSSPropertyValue *shorthand;
  SAC_Parser parser;
  CSSOM_CSSPropertyType type;
  const char *name;
  const SAC_LexicalUnit **holder;
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

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->type);
  _size = 0;
  _isInherit = 1;
  for (i = 0; i < setting->nsubtypes; ++i) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, setting->subtypes[i]);

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
  struct _CSSOM_LexicalUnitRange *values)
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

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->type);

  if (!testShorthand(shorthand, &size, &isInherit)) return 0;
  if (isInherit) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues, setting->subtypes[0]);
    _CSSOM_SET_RANGE(values, 0, shorthand->type, property->begin,
      property->end);
  } else {
    holder = (const SAC_LexicalUnit **)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * size);
    if (holder == NULL) return -1;
    wit = holder;
    for (i = 0; i < setting->nsubtypes; ++i) {
      property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
        shorthand->parentValues, setting->subtypes[i]);

      for (rit = property->begin; rit != property->end; ++rit, ++wit)
        *wit = *rit;
    }
    rval = setting->handler(shorthand->cssom, holder, wit, NULL) == wit;
    CSSOM_free(holder);
    if (!rval) return 0;

    for (i = 0; i < setting->nsubtypes; ++i) {
      property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
        shorthand->parentValues, setting->subtypes[i]);
      _CSSOM_SET_RANGE(values, i, property->type, property->begin,
        property->end);
    }
  }

  return 0;
}



int CSSOM_CSSPropertyValue__omitBoxShorthand(
  const CSSOM_CSSPropertyValue *shorthand,
  struct _CSSOM_LexicalUnitRange *values)
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

  setting = CSSOM__propertySetting(shorthand->cssom, shorthand->type);

  top = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subtypes[0]);
  right = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subtypes[1]);
  bottom = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subtypes[2]);
  left = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    shorthand->parentValues, setting->subtypes[3]);



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
    rval = setting->handler(shorthand->cssom, holder, wit, NULL) == wit;
    CSSOM_free(holder);
    if (!rval) return 0;
  }

  if (rightleft) {
    if (topbottom) {
      if (topright) {
        _CSSOM_SET_RANGE(values, 0, setting->subtypes[0], top->begin, top->end);
      } else {
        _CSSOM_SET_RANGE(values, 0, setting->subtypes[0], top->begin, top->end);
        _CSSOM_SET_RANGE(values, 1, setting->subtypes[1], right->begin,
          right->end);
      }
    } else {
      _CSSOM_SET_RANGE(values, 0, setting->subtypes[0], top->begin, top->end);
      _CSSOM_SET_RANGE(values, 1, setting->subtypes[1], right->begin,
        right->end);
      _CSSOM_SET_RANGE(values, 2, setting->subtypes[2], bottom->begin,
        bottom->end);
    }
  } else {
    _CSSOM_SET_RANGE(values, 0, setting->subtypes[0], top->begin, top->end);
    _CSSOM_SET_RANGE(values, 1, setting->subtypes[1], right->begin, right->end);
    _CSSOM_SET_RANGE(values, 2, setting->subtypes[2], bottom->begin,
      bottom->end);
    _CSSOM_SET_RANGE(values, 3, setting->subtypes[3], left->begin, left->end);
  }

  return 0;
}



static int CSSPropertyValue_emit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  struct _CSSOM_LexicalUnitRange *values;
  size_t i;
  int rval;

  setting = CSSOM__propertySetting(property->cssom, property->type);

  if (setting->omit == NULL)
    return LexicalUnitRange__emit(property->begin, property->end, out);

  values = (struct _CSSOM_LexicalUnitRange *)CSSOM_malloc(
    sizeof(struct _CSSOM_LexicalUnitRange) * setting->nsubtypes);
  if (values == NULL) return -1;

  for (i = 0; i < setting->nsubtypes; ++i)
    _CSSOM_SET_RANGE(values, i, 0, NULL, NULL);

  rval = setting->omit(property, values);
  if (rval != 0) {
    CSSOM_free(values);
    return rval;
  }

  if (values[0].begin != NULL) {
    rval = LexicalUnitRange__emit(values[0].begin, values[0].end, out);
    if (rval != 0) {
      CSSOM_free(values);
      return rval;
    }
  }

  for (i = 1; i < setting->nsubtypes; ++i) {
    if (values[i].begin == NULL) break;

    fprintf(out, " ");
    rval = LexicalUnitRange__emit(values[i].begin, values[i].end, out);
    if (rval != 0) {
      CSSOM_free(values);
      return rval;
    }
  }

  CSSOM_free(values);
  return 0;
}



static CSSOM_CSSPropertyValue* CSSPropertyValue_alloc(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyValue *shorthand, CSSOM_CSSPropertyType type,
  const SAC_LexicalUnit **holder, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, SAC_Boolean important)
{
  CSSOM_CSSPropertyValue *property;

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) return NULL;

  property->handles = 1;
  property->cssom = cssom;
  property->parentValues = parentValues;
  property->shorthand = shorthand;
  property->parser = NULL;
  property->type = type;
  property->name = CSSOM__propertySetting(cssom, type)->name;
  property->holder = holder;
  property->begin = begin;
  property->end = end;
  property->important = important;
  property->cssText = NULL;

  return property;
}



static CSSOM_CSSPropertyValue* assignProperties(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *parentValues, const SAC_LexicalUnit **holder,
  struct _CSSOM_LexicalUnitRange *values, size_t size, SAC_Boolean important,
  int *error)
{
  CSSOM_CSSPropertyValue *shorthand;
  CSSOM_CSSPropertyValue *property;
  size_t i;
  int rval;

  if (values[0].begin == NULL) {
    if (error != NULL) *error = 1;
    return NULL;
  }

  shorthand = CSSPropertyValue_alloc(cssom, parentValues, NULL,
      values[0].type, holder, values[0].begin, values[0].end, important);
  if (shorthand == NULL) {
    if (error != NULL) *error = -1;
    return NULL;
  }

  for (i = 1; i < size; ++i) {
    if (values[i].begin == NULL) continue;

    property = CSSPropertyValue_alloc(cssom, parentValues, shorthand,
      values[i].type, NULL, values[i].begin, values[i].end, important);
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
  CSSOM_CSSStyleDeclarationValue *parentValues,
  CSSOM_CSSPropertyType type, const SAC_LexicalUnit *value,
  SAC_Boolean important, int *error)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  /**
   * The largest one.
   */
  struct _CSSOM_LexicalUnitRange values[] = {
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL },
    { 0, NULL, NULL }
  };

  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  const SAC_LexicalUnit **holder;
  CSSOM_CSSPropertyValue *property;

  setting = CSSOM__propertySetting(cssom, type);

  if (value->lexicalUnitType != SAC_SUB_EXPRESSION) {
    holder = (const SAC_LexicalUnit**)CSSOM_malloc(
      sizeof(const SAC_LexicalUnit*) * 2);
    if (holder == NULL) return NULL;
    holder[0] = value;
    holder[1] = NULL;
    begin = &holder[0];
    end = &holder[1];
  } else {
    holder = NULL;
    begin = (const SAC_LexicalUnit**)value->desc.subValues;
    end = begin;
    while (*end != NULL) ++end;
  }

  if (setting->handler(cssom, begin, end, values) != end) {
    CSSOM_free(holder);
    if (error != NULL) *error = 1;
    return NULL;
  }

  /**
   * FIXME: Drop this line after CSSOM_LexicalUnitRange_whatever cleanup.
   */
  values[0].type = type;

  property = assignProperties(cssom, parentValues, holder, values,
    setting->nsubtypes + 1, important, error);
  if (property == NULL) {
    CSSOM_free(holder);
    if (error != NULL) *error = 1;
    return NULL;
  }
  
  if (error != NULL) *error = 0;
  return property;
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
  CSSOM_free(property->holder);
  SAC_DisposeParser(property->parser);
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
  assert(lhs->parentValues == rhs->parentValues);
  SWAPP(lhs->shorthand, rhs->shorthand);
  SWAPP(lhs->parser, rhs->parser);
  SWAPS(lhs->type, rhs->type);
  SWAPP(lhs->name, rhs->name);
  SWAPP(lhs->holder, rhs->holder);
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
    property->parentValues, property->type, cssText, strlen(cssText), NULL, 0);
  if (newProperty == NULL) return;

  CSSPropertyValue_swap(property, newProperty);

  CSSOM_CSSPropertyValue_release(newProperty);
}



int CSSOM_CSSPropertyValue__important(const CSSOM_CSSPropertyValue *property) {
  return property->important == SAC_TRUE ? 1 : 0;
}




void CSSOM_CSSPropertyValue__keepParser(CSSOM_CSSPropertyValue *property,
  SAC_Parser parser)
{
  assert(property->parser == NULL);
  property->parser = parser;
}
