#include "CSSPropertyValue.h"

#include "CSSEmitter.h"
#include "memory.h"

#include <cssom/CSSStyleDeclarationValue.h>

#include <assert.h>
#include <stdio.h>



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
  CSSOM_CSSStyleDeclarationValue *parentValues,
  const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSPropertyValue *property;

  property = (CSSOM_CSSPropertyValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSPropertyValue));
  if (property == NULL) return NULL;

  property->handles = 1;
  property->parentValues = parentValues;
  property->parser = NULL;
  property->name = NULL;
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



void CSSOM_CSSPropertyValue__setName(CSSOM_CSSPropertyValue *property,
  const char *name)
{
  property->name = name;
  CSSOM_native_free(property->cssText);
  property->cssText = NULL;
}



const char* CSSOM_CSSPropertyValue__name(
  const CSSOM_CSSPropertyValue *property)
{
  return property->name;
}



const char* CSSOM_CSSPropertyValue_cssText(
  const CSSOM_CSSPropertyValue *property)
{
  if (property->cssText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_lexicalUnit(out, property->value) != 0) {
      fclose(out);
      CSSOM_native_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_native_free(buf);
      return NULL;
    }

    ((CSSOM_CSSPropertyValue*)property)->cssText = buf;
  }
  return property->cssText;
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
