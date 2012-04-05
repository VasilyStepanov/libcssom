#include "CSSStyleDeclaration.h"

#include "CSSProperty.h"
#include "CSSEmitter.h"
#include "memory.h"

#include <stdio.h>
#include <assert.h>



struct _CSSOM_CSSStyleDeclaration {
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

  style->fsm = fsm;
  style->cssText = NULL;

  return style;
}



void CSSOM_CSSStyleDeclaration__free(CSSOM_CSSStyleDeclaration *style) {
  CSSOM_FSMIter_CSSProperty it;

  for (
    it = CSSOM_FSM_CSSProperty_begin(style->fsm);
    it != CSSOM_FSM_CSSProperty_end(style->fsm);
    it = CSSOM_FSMIter_CSSProperty_next(it))
  {
    CSSOM_CSSProperty__free(it->value);
  }

  CSSOM_native_free(style->cssText);
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
    CSSOM_CSSProperty__free(prop);
    return NULL;
  }

  CSSOM_native_free(style->cssText);
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

    if (CSSOM_CSSEmitter_cssStyleDeclaration(out, style) != 0) {
      fclose(out);
      CSSOM_native_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_native_free(buf);
      return NULL;
    }

    ((CSSOM_CSSStyleDeclaration*)style)->cssText = buf;
  }
  return style->cssText;
}



CSSOM_CSSStyleDeclarationIter CSSOM_CSSStyleDeclaration__begin(
  CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_begin(style->fsm);
}



CSSOM_CSSStyleDeclarationIter CSSOM_CSSStyleDeclaration__end(
  CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_end(style->fsm);
}



CSSOM_CSSStyleDeclarationIter
CSSOM_CSSStyleDeclarationIter_next(
  CSSOM_CSSStyleDeclarationIter iter)
{
  return CSSOM_FSMIter_CSSProperty_next(iter);
}



CSSOM_CSSStyleDeclarationConstIter CSSOM_CSSStyleDeclaration__cbegin(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_cbegin(style->fsm);
}



CSSOM_CSSStyleDeclarationConstIter CSSOM_CSSStyleDeclaration__cend(
  const CSSOM_CSSStyleDeclaration *style)
{
  return CSSOM_FSM_CSSProperty_cend(style->fsm);
}



CSSOM_CSSStyleDeclarationConstIter
CSSOM_CSSStyleDeclarationConstIter_next(
  CSSOM_CSSStyleDeclarationConstIter iter)
{
  return CSSOM_FSMConstIter_CSSProperty_next(iter);
}
