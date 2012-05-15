#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleDeclaration.h"
#include "CSSStyleDeclarationValue.h"
#include "CSSStyleSheet.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclarationValue.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



struct _CSSOM_CSSPropertyValue {
  size_t handles;
  CSSOM_CSSStyleDeclarationValue *parentValues;
  SAC_Parser parser;
  const char *name;
  const SAC_LexicalUnit *value;
  SAC_Boolean important;
  char *cssText;
};



CSSOM_CSSPropertyValue* CSSOM_CSSPropertyValue__alloc(
  CSSOM_CSSStyleDeclarationValue *parentValues, const char *name,
  const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSPropertyValue *property;

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) return NULL;

  property->handles = 1;
  property->parentValues = parentValues;
  property->parser = NULL;
  property->name = name;
  property->value = value;
  property->important = important;
  property->cssText = NULL;

  return property;
}



void CSSOM_CSSPropertyValue_acquire(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  ++property->handles;
  CSSOM_CSSStyleDeclarationValue_acquire(property->parentValues);
}



void CSSOM_CSSPropertyValue_release(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  assert(property->handles > 0);
  --property->handles;
  if (property->handles > 0) {
    CSSOM_CSSStyleDeclarationValue_release(property->parentValues);
    return;
  }

  CSSOM_native_free(property->cssText);
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

  if (CSSOM_CSSEmitter_property(out, property) != 0) {
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
  SWAP(lhs->parser, rhs->parser);
  SWAP(lhs->name, rhs->name);
  SWAP(lhs->value, rhs->value);
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
        CSSOM_CSSStyleDeclarationValue_parentStyle(property->parentValues))));
  newProperty = CSSOM__parsePropertyValue(cssom, property->parentValues,
    property->name, cssText, strlen(cssText), NULL, 0);
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



const SAC_LexicalUnit* CSSOM_CSSPropertyValue__value(
  const CSSOM_CSSPropertyValue *property)
{
  return property->value;
}
