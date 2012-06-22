#include "CSSPropertyData.h"

#include "memory.h"

#include <assert.h>



struct _CSSOM_CSSPropertyData {
  size_t handles;
  SAC_Parser parser;
  const SAC_LexicalUnit **holder;
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
};



CSSOM_CSSPropertyData* CSSOM_CSSPropertyData__alloc(
  const SAC_LexicalUnit *value)
{
  const SAC_LexicalUnit **begin;
  const SAC_LexicalUnit **end;
  const SAC_LexicalUnit **holder;
  CSSOM_CSSPropertyData *data;

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

  data = (CSSOM_CSSPropertyData*)CSSOM_malloc(sizeof(CSSOM_CSSPropertyData));
  if (data == NULL) {
    CSSOM_free(holder);
    return NULL;
  }

  data->handles = 1;
  data->holder = holder;
  data->begin = begin;
  data->end = end;
  data->parser = NULL;

  return data;
}



void CSSOM_CSSPropertyData_acquire(CSSOM_CSSPropertyData *data) {
  if (data == NULL) return;

  ++data->handles;
}


void CSSOM_CSSPropertyData_release(CSSOM_CSSPropertyData *data) {
  if (data == NULL) return;

  assert(data->handles > 0);
  --data->handles;
  if (data->handles > 0) return;

  CSSOM_free(data->holder);
  SAC_DisposeParser(data->parser);
  CSSOM_free(data);
}



const SAC_LexicalUnit** CSSOM_CSSPropertyData_begin(
  const CSSOM_CSSPropertyData *data)
{
  return data->begin;
}


const SAC_LexicalUnit** CSSOM_CSSPropertyData_end(
  const CSSOM_CSSPropertyData *data)
{
  return data->end;
}



void CSSOM_CSSPropertyData__keepParser(CSSOM_CSSPropertyData *data,
  SAC_Parser parser)
{
  assert(data->parser == NULL);
  data->parser = parser;
}
