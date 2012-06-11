#include "CSSStyleDeclarationValue.h"

#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSPropertyValue.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSStyleDeclaration.h>
#include <cssom/CSSStyleRule.h>

#include <assert.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>



struct _CSSOM_CSSStyleDeclarationValue {
  size_t handles;
  CSSOM_CSSStyleDeclaration *parentStyle;
  CSSOM_FSM_CSSPropertyValue *fsm;
  char *removedPropertyHolder;
};



int CSSOM_CSSStyleDeclarationValue__assignProperties(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyValue **properties,
  size_t size)
{
  const CSSOM *cssom;
  size_t i;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  for (i = 0; i < size; ++i) {
    propertyValue = properties[i];

    if (propertyValue == NULL) continue;

    it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm,
      CSSOM_CSSPropertyValue__name(propertyValue), NULL);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

    if (it->value != NULL) {
      it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
      if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return -1;
      CSSOM_CSSPropertyValue_release(it->value);
    }
    it->value = propertyValue;
  }

  return 0;
}



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclarationValue__alloc(
  CSSOM_CSSStyleDeclaration *parentStyle)
{
  const CSSOM_FSMTable_CSSPropertyValue *table;
  CSSOM_CSSStyleDeclarationValue *values;
  CSSOM_FSM_CSSPropertyValue *fsm;

  table = CSSOM__table(
    CSSOM_CSSStyleSheet__cssom(
      CSSOM_CSSRule_parentStyleSheet(
        CSSOM_CSSStyleDeclaration_parentRule(parentStyle))));

  fsm = CSSOM_FSM_CSSPropertyValue_alloc(table);
  if (fsm == NULL) return NULL;

  values = (CSSOM_CSSStyleDeclarationValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclarationValue));
  if (values == NULL) {
    CSSOM_FSM_CSSPropertyValue_free(fsm);
    return NULL;
  }

  values->handles = 1;
  values->parentStyle = parentStyle;
  values->fsm = fsm;
  values->removedPropertyHolder = NULL;

  return values;
}



void CSSOM_CSSStyleDeclarationValue_acquire(
  CSSOM_CSSStyleDeclarationValue *values)
{
  if (values == NULL) return;

  ++values->handles;
  CSSOM_CSSStyleDeclaration_acquire(values->parentStyle);
}



void CSSOM_CSSStyleDeclarationValue_release(
  CSSOM_CSSStyleDeclarationValue *values)
{
  CSSOM_FSMIter_CSSPropertyValue it;
  
  if (values == NULL) return;

  assert(values->handles > 0);
  --values->handles;
  if (values->handles > 0) {
    CSSOM_CSSStyleDeclaration_release(values->parentStyle);
    return;
  }

  CSSOM_native_free(values->removedPropertyHolder);
  for (
    it = CSSOM_FSM_CSSPropertyValue_begin(values->fsm);
    it != CSSOM_FSM_CSSPropertyValue_end(values->fsm);
    it = CSSOM_FSMIter_CSSPropertyValue_next(it))
  {
    CSSOM_CSSPropertyValue_release(it->value);
  }
  CSSOM_FSM_CSSPropertyValue_free(values->fsm);
  CSSOM_free(values);
}



CSSOM_CSSStyleDeclaration* CSSOM_CSSStyleDeclarationValue__parentStyle(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return values->parentStyle;
}



unsigned long CSSOM_CSSStyleDeclarationValue_length(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_size(values->fsm);
}



const char* CSSOM_CSSStyleDeclarationValue_item(
  CSSOM_CSSStyleDeclarationValue *values, unsigned long index)
{
  CSSOM_FSMConstIter_CSSPropertyValue match;

  if (index >= CSSOM_FSM_CSSPropertyValue_size(values->fsm)) return NULL;

  match = CSSOM_FSM_CSSPropertyValue_at(values->fsm, index);

  return CSSOM_CSSPropertyValue__name(match->value);
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue_getProperty(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_find(values->fsm, property);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  return it->value;
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue__fgetProperty(
  const CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  return it->value;
}



const char* CSSOM_CSSStyleDeclarationValue__fgetPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue__fgetProperty(values, property);
  if (value == NULL) return NULL;

  return CSSOM_CSSPropertyValue_cssText(value);
}



int CSSOM_CSSStyleDeclarationValue__setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const SAC_LexicalUnit **begin,
  const SAC_LexicalUnit **end, SAC_Boolean priority)
{
  const CSSOM *cssom;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  int error;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

  propertyValue = CSSOM_CSSPropertyValue__alloc(cssom, values, NULL, it->hash,
    begin, end, priority, &error);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return error;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return -1;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

  return 0;
}



void CSSOM_CSSStyleDeclarationValue_setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value)
{
  CSSOM_CSSStyleDeclarationValue_setPropertyEx(values, property, value, NULL);
}



void CSSOM_CSSStyleDeclarationValue_setPropertyEx(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const char *value, const char *priority)
{
  const CSSOM *cssom;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  int priorityLen;

  if (property == NULL) return;
  if (value == NULL) {
    CSSOM_CSSStyleDeclarationValue_removeProperty(values, property);
    return;
  }

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  if (priority == NULL) {
    priorityLen = 0;
  } else {
    priorityLen = strlen(priority);
  }
  propertyValue = CSSOM__parsePropertyValue(cssom, values, it->hash, value,
    strlen(value), priority, priorityLen);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

}



static void CSSStyleDeclarationValue__fremoveProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue match;
  
  match = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  if (match == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  CSSOM_CSSPropertyValue_release(match->value);
  CSSOM_FSM_CSSPropertyValue_erase(values->fsm, match);
}



void CSSOM_CSSStyleDeclarationValue__fsetProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  CSSOM_CSSPropertyType property, const char *value)
{
  const CSSOM *cssom;
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  const char *sproperty;

  if (value == NULL) {
    CSSStyleDeclarationValue__fremoveProperty(values, property);
    return;
  }

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));

  sproperty = CSSOM__properties(cssom)[property];

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, sproperty, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  propertyValue = CSSOM__parsePropertyValue(cssom, values, it->hash, value,
    strlen(value), NULL, 0);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      CSSOM_CSSPropertyValue_release(propertyValue);
      return;
    }
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = propertyValue;

}



const char* CSSOM_CSSStyleDeclarationValue_removeProperty(
  CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSPropertyValue match;
  
  match = CSSOM_FSM_CSSPropertyValue_find(values->fsm, property);
  if (match == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  CSSOM_native_free(values->removedPropertyHolder);
  values->removedPropertyHolder = strdup(CSSOM_CSSPropertyValue_cssText(
    match->value));

  CSSOM_CSSPropertyValue_release(match->value);
  CSSOM_FSM_CSSPropertyValue_erase(values->fsm, match);

  return values->removedPropertyHolder;
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__begin(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_begin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__end(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_end(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter
CSSOM_CSSStyleDeclarationValueIter_next(
  CSSOM_CSSStyleDeclarationValueIter iter)
{
  return CSSOM_FSMIter_CSSPropertyValue_next(iter);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cbegin(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_cbegin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cend(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSPropertyValue_cend(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter
CSSOM_CSSStyleDeclarationValueConstIter_next(
  CSSOM_CSSStyleDeclarationValueConstIter iter)
{
  return CSSOM_FSMConstIter_CSSPropertyValue_next(iter);
}




