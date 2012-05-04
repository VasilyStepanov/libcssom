#include "CSSStyleDeclarationValue.h"

#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSPropertyValue.h"
#include "memory.h"

#include <cssom/CSSStyleDeclaration.h>
#include <cssom/CSSStyleRule.h>

#include <assert.h>
#include <string.h>



struct _CSSOM_CSSStyleDeclarationValue {
  size_t handles;
  CSSOM_CSSStyleDeclaration *parentStyle;
  CSSOM_FSM_CSSPropertyValue *fsm;
  char *removedPropertyHolder;
};



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
  if (values == NULL) return;

  assert(values->handles > 0);
  --values->handles;
  if (values->handles > 0) {
    CSSOM_CSSStyleDeclaration_release(values->parentStyle);
    return;
  }

  CSSOM_native_free(values->removedPropertyHolder);
  CSSOM_FSM_CSSPropertyValue_free(values->fsm);
  CSSOM_free(values);
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



const char* CSSOM_CSSStyleDeclarationValue__getPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(values, property);

  if (value == NULL) return NULL;

  return CSSOM_CSSPropertyValue_cssText(value);
}



const char* CSSOM_CSSStyleDeclarationValue__getPropertyPriority(
  const CSSOM_CSSStyleDeclarationValue *values, const char * property)
{
  CSSOM_CSSPropertyValue *value;

  value = CSSOM_CSSStyleDeclarationValue_getProperty(values, property);

  if (value == NULL) return "";
  if (CSSOM_CSSPropertyValue__important(value) == 0) return "";

  return "important";
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue__setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean priority)
{
  CSSOM_CSSPropertyValue *propertyValue;
  CSSOM_FSMIter_CSSPropertyValue it;

  propertyValue = CSSOM_CSSPropertyValue__alloc(values, value, priority);
  if (propertyValue == NULL) return NULL;

  it = CSSOM_FSM_CSSPropertyValue_add(values->fsm, property, propertyValue);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
    CSSOM_CSSPropertyValue_release(propertyValue);
    return NULL;
  }

  CSSOM_CSSPropertyValue__setName(propertyValue, it->key);

  return propertyValue;
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
  CSSOM_CSSPropertyValue *propertyValue;
  CSSOM_FSMIter_CSSPropertyValue it;
  int priorityLen;

  if (property == NULL) return;
  if (value == NULL) {
    CSSOM_CSSStyleDeclarationValue_removeProperty(values, property);
    return;
  }

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(values->parentStyle)));
  if (priority == NULL) {
    priorityLen = 0;
  } else {
    priorityLen = strlen(priority);
  }
  propertyValue = CSSOM__parsePropertyValue(cssom, values,
    value, strlen(value), priority, priorityLen);
  if (propertyValue == NULL) return;

  it = CSSOM_FSM_CSSPropertyValue_add(values->fsm, property, propertyValue);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
    CSSOM_CSSPropertyValue_release(propertyValue);
    return;
  }

  CSSOM_CSSPropertyValue__setName(propertyValue, it->key);
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




