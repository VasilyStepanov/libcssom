#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "CSSPropertyValue_background.h"
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



static int CSSPropertyValue_isInherit(const CSSOM_CSSPropertyValue *property) {
  if (property->end - property->begin != 1) return 0;
  return CSSOM_LexicalUnit_isInherit(property->begin[0]);
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



int CSSOM_CSSPropertyValue__genericEmit(const CSSOM_CSSPropertyValue *property,
  FILE *out)
{
  const SAC_LexicalUnit **it;

  it = property->begin;
  if (it != property->end) {
    if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    while (++it != property->end) {
      if (fprintf(out, " ") < 0) return 1;
      if (CSSOM_CSSEmitter_lexicalUnit(out, *it) != 0) return 1;
    }
  }

  return 0;
}



static int isInheritShorthand(const CSSOM_CSSPropertyValue *shorthand) {
  size_t i;
  CSSOM_CSSPropertyValue *property;

  for (i = 0; i < CSSOM_propertySettings[shorthand->type].nsubtypes; ++i) {
    property = CSSOM_CSSStyleDeclarationValue__fgetProperty(
      shorthand->parentValues,
      CSSOM_propertySettings[shorthand->type].subtypes[i]);

    if (property == NULL) return 0;
    if (property->end - property->begin != 1) return 0;
    if (CSSOM_LexicalUnit_isInherit(property->begin[0]) == 0) return 0;
  }
  return 1;
}



int CSSOM_CSSPropertyValue__genericShorthandEmit(
  const CSSOM_CSSPropertyValue *property, FILE *out)
{
  size_t i;
  int emited;
  const char *cssText;

  if (isInheritShorthand(property)) {
    cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
      property->parentValues,
      CSSOM_propertySettings[property->type].subtypes[0]);
    if (fprintf(out, "%s", cssText) < 0) return 1;
    return 0;
  }

  emited = 0;
  for (i = 0; i < CSSOM_propertySettings[property->type].nsubtypes; ++i) {
    cssText = CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
      property->parentValues,
      CSSOM_propertySettings[property->type].subtypes[i]);
    if (cssText != NULL) {
      if (emited) {
        if (fprintf(out, " ") < 0) return 1;
      } else {
        emited = 1;
      }
      if (fprintf(out, "%s", cssText) < 0) return 1;
    }
  }

  return 0;
}



int CSSOM_CSSPropertyValue__boxShorthandEmit(
  const CSSOM_CSSPropertyValue *property, FILE *out)
{
  CSSOM_CSSPropertyValue *top;
  CSSOM_CSSPropertyValue *right;
  CSSOM_CSSPropertyValue *bottom;
  CSSOM_CSSPropertyValue *left;
  CSSOM_CSSPropertyValue *print[4] = { NULL, NULL, NULL, NULL };
  size_t i;
  const char *cssText;
  int topbottom;
  int rightleft;
  int topright;

  top = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, CSSOM_propertySettings[property->type].subtypes[0]);
  right = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, CSSOM_propertySettings[property->type].subtypes[1]);
  bottom = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, CSSOM_propertySettings[property->type].subtypes[2]);
  left = CSSOM_CSSStyleDeclarationValue__fgetProperty(
    property->parentValues, CSSOM_propertySettings[property->type].subtypes[3]);



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

  if (!(rightleft && topbottom && topright)) {
    if (CSSPropertyValue_isInherit(top) ||
      CSSPropertyValue_isInherit(right) ||
      CSSPropertyValue_isInherit(bottom) ||
      CSSPropertyValue_isInherit(left))
    {
      return 0;
    }
  }

  if (rightleft) {
    if (topbottom) {
      if (topright) {
        print[0] = top;
      } else {
        print[0] = top;
        print[1] = right;
      }
    } else {
      print[0] = top;
      print[1] = right;
      print[2] = bottom;
    }
  } else {
    print[0] = top;
    print[1] = right;
    print[2] = bottom;
    print[3] = left;
  }

  for (i = 0; i < 4; ++i) {
    if (print[i] == NULL) break;

    cssText = CSSOM_CSSPropertyValue_cssText(print[i]);

    if (cssText == NULL) return 1;
    if (i != 0) {
      if (fprintf(out, " ") < 0) return 1;
    }
    if (fprintf(out, "%s", cssText) < 0) return 1;
  }

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
  property->parentValues = parentValues;
  property->shorthand = shorthand;
  property->parser = NULL;
  property->type = type;
  property->name = CSSOM__properties(cssom)[type];
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

  if (CSSOM_propertySettings[type].handler(begin, end, values) != end) {
    CSSOM_free(holder);
    if (error != NULL) *error = 1;
    return NULL;
  }

  /**
   * FIXME: Drop this line after CSSOM_LexicalUnitRange_whatever cleanup.
   */
  values[0].type = type;

  property = assignProperties(cssom, parentValues, holder, values,
    CSSOM_propertySettings[type].nsubtypes + 1, important, error);
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

  if (CSSOM_propertySettings[property->type].emit(property, out) != 0) {
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
  SWAP(lhs->parentValues, rhs->parentValues);
  SWAP(lhs->shorthand, rhs->shorthand);
  SWAP(lhs->parser, rhs->parser);
  SWAPS(lhs->type, rhs->type);
  SWAP(lhs->name, rhs->name);
  SWAP(lhs->holder, rhs->holder);
  SWAP(lhs->begin, rhs->begin);
  SWAP(lhs->end, rhs->end);
  SWAPS(lhs->important, rhs->important);
  SWAP(lhs->cssText, rhs->cssText);
}



void CSSOM_CSSPropertyValue_setCSSText(CSSOM_CSSPropertyValue *property,
  const char * cssText)
{
  const CSSOM *cssom;
  CSSOM_CSSPropertyValue *newProperty;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(
        CSSOM_CSSStyleDeclarationValue__parentStyle(property->parentValues))));
  newProperty = CSSOM__parsePropertyValue(cssom, property->parentValues,
    property->type, cssText, strlen(cssText), NULL, 0);
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
