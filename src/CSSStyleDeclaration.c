#include "CSSStyleDeclaration.h"

#include "CSSProperty.h"
#include "CSSEmitter.h"
#include "memory.h"

#include <stdio.h>
#include <assert.h>



struct _CSSOM_CSSStyleDeclaration {
  size_t handles;
  CSSOM_FSM_CSSProperty *fsm;
  char *cssText;
};



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclaration__alloc(
  const CSSOM_FSMTable_CSSProperty *table)
{
  CSSOM_CSSStyleDeclaration *style;
  CSSOM_FSM_CSSProperty *fsm;

  fsm = CSSOM_FSM_CSSProperty_alloc(table);
  if (fsm == NULL) return NULL;

  style = (CSSOM_CSSStyleDeclaration*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclaration));
  if (style == NULL) {
    CSSOM_FSM_CSSProperty_free(fsm);
    return NULL;
  }

  style->handles = 1;
  style->fsm = fsm;
  style->cssText = NULL;

  return style;
}



void CSSOM_CSSStyleDeclaration_acquire(CSSOM_CSSStyleDeclaration *style) {
  ++style->handles;
}



void CSSOM_CSSStyleDeclaration_release(CSSOM_CSSStyleDeclaration *style) {
  CSSOM_FSMIter_CSSProperty it;

  assert(style->handles > 0);
  --style->handles;
  if (style->handles > 0) return;

  for (
    it = CSSOM_FSM_CSSProperty_begin(style->fsm);
    it != CSSOM_FSM_CSSProperty_end(style->fsm);
    it = CSSOM_FSMIter_CSSProperty_next(it))
  {
    CSSOM_CSSProperty_release(it->value);
  }

  CSSOM_free(style->cssText);
  CSSOM_FSM_CSSProperty_free(style->fsm);
  CSSOM_free(style);
}



unsigned long CSSOM_CSSStyleDeclaration_length(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_size(style->fsm);
}



CSSOM_CSSProperty* CSSOM_CSSStyleDeclaration__setProperty(
  CSSOM_CSSStyleDeclaration *style,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSProperty *prop;
  CSSOM_FSMIter_CSSProperty it;

  prop = CSSOM_CSSProperty__alloc(value, important);
  if (prop == NULL) return NULL;

  it = CSSOM_FSM_CSSProperty_add(style->fsm, property, prop);
  if (it == CSSOM_FSM_CSSProperty_end(style->fsm)) {
    CSSOM_CSSProperty_release(prop);
    return NULL;
  }

  CSSOM_free(style->cssText);
  style->cssText = NULL;

  CSSOM_CSSProperty__setName(prop, it->key);

  return prop;
}



const char* CSSOM_CSSStyleDeclaration_getPropertyValue(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_FSMIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_find(style->fsm, property);
  if (it == CSSOM_FSM_CSSProperty_end(style->fsm)) return NULL;

  return CSSOM_CSSProperty_cssText(it->value);
}



const char* CSSOM_CSSStyleDeclaration_getPropertyPriority(
  const CSSOM_CSSStyleDeclaration *style, const char *property)
{
  CSSOM_FSMIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_find(style->fsm, property);
  if (it == CSSOM_FSM_CSSProperty_end(style->fsm)) return "";

  if (CSSOM_CSSProperty_important(it->value) == 0) return "";

  return "important";
}



static int emit_cssStyleDeclaration(FILE *out,
  const CSSOM_CSSStyleDeclaration *style)
{
  CSSOM_FSMConstIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_cbegin(style->fsm);
  if (it != CSSOM_FSM_CSSProperty_cend(style->fsm)) {
    if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;
    if (fprintf(out, ";") < 0) return 1;

    for (
      it = CSSOM_FSMConstIter_CSSProperty_next(it);
      it != CSSOM_FSM_CSSProperty_cend(style->fsm);
      it = CSSOM_FSMConstIter_CSSProperty_next(it))
    {
      if (fprintf(out, " ") < 0) return 1;
      if (CSSOM_CSSEmitter_cssProperty(out, it->value) != 0) return 1;
      if (fprintf(out, ";") < 0) return 1;
    }
  }

  return 0;
}



const char* CSSOM_CSSStyleDeclaration_cssText(
  const CSSOM_CSSStyleDeclaration *style)
{
  if (style->cssText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (emit_cssStyleDeclaration(out, style) != 0) {
      fclose(out);
      CSSOM_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleDeclaration*)style)->cssText = buf;
  }
  return style->cssText;
}
