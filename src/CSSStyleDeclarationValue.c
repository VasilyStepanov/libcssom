#include "CSSStyleDeclarationValue.h"

#include "CSSOM.h"
#include "CSSPropertySetting.h"
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
  const CSSOM *cssom;
  CSSOM_CSSStyleDeclaration *parentStyle;
  CSSOM_FSM_CSSPropertyValue *fsm;
  char *removedPropertyHolder;
};



int CSSOM_CSSStyleDeclarationValue__assignProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyValue *property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm,
    CSSOM_CSSPropertyValue__name(property), NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

  if (it->value != NULL) {
    it = CSSOM_FSM_CSSPropertyValue_update(values->fsm, it);
    if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return -1;
    CSSOM_CSSPropertyValue_release(it->value);
  }
  it->value = property;

  return 0;
}



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclarationValue__alloc(
  CSSOM_CSSStyleDeclaration *parentStyle)
{
  const CSSOM *cssom;
  CSSOM_CSSStyleDeclarationValue *values;
  CSSOM_FSM_CSSPropertyValue *fsm;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(
      CSSOM_CSSStyleDeclaration_parentRule(parentStyle)));

  fsm = CSSOM_FSM_CSSPropertyValue_alloc(CSSOM__table(cssom));
  if (fsm == NULL) return NULL;

  values = (CSSOM_CSSStyleDeclarationValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclarationValue));
  if (values == NULL) {
    CSSOM_FSM_CSSPropertyValue_free(fsm);
    return NULL;
  }

  values->handles = 1;
  values->cssom = cssom;
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



void CSSOM_CSSStyleDeclarationValue__setParentStyle(
  CSSOM_CSSStyleDeclarationValue *values,
  CSSOM_CSSStyleDeclaration *parentStyle)
{
  size_t i;

  for (i = 0; i < values->handles - 1; ++i) {
    CSSOM_CSSStyleDeclaration_release(values->parentStyle);
    CSSOM_CSSStyleDeclaration_acquire(parentStyle);
  }

  values->parentStyle = parentStyle;
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



static void CSSStyleDeclarationValue__fremoveProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property);



static CSSOM_CSSPropertyValue* CSSStyleDeclarationValue__getProperty(
  const CSSOM_CSSStyleDeclarationValue *values CSSOM_UNUSED,
  CSSOM_FSMIter_CSSPropertyValue iter)
{
  if (iter == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return NULL;

  return iter->value;
}



static CSSOM_CSSPropertyValue* CSSStyleDeclarationValue__addProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_FSMIter_CSSPropertyValue iter,
  CSSOM_CSSPropertyValue *property)
{
  if (iter->value != NULL) {
    iter = CSSOM_FSM_CSSPropertyValue_update(values->fsm, iter);
    if (iter == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) {
      if (iter->value == NULL)
        CSSOM_FSM_CSSPropertyValue_erase(values->fsm, iter);
      return NULL;
    }
    CSSOM_CSSPropertyValue_release(iter->value);
  }
  iter->value = property;

  return property;
}



static void CSSStyleDeclarationValue__eraseProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_FSMIter_CSSPropertyValue iter)
{
  const struct _CSSOM_CSSPropertySetting *setting;
  size_t i;
  
  setting = CSSOM__propertySetting(values->cssom, iter->hash);

  for (i = 0; i < setting->nsubtypes; ++i)
    CSSStyleDeclarationValue__fremoveProperty(values, setting->subtypes[i]);

  CSSOM_CSSPropertyValue_release(iter->value);
  CSSOM_FSM_CSSPropertyValue_erase(values->fsm, iter);
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue_getProperty(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_find(values->fsm, property);
  return CSSStyleDeclarationValue__getProperty(values, it);
}



CSSOM_CSSPropertyValue* CSSOM_CSSStyleDeclarationValue__fgetProperty(
  const CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue it;

  it = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  return CSSStyleDeclarationValue__getProperty(values, it);
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
  CSSOM_CSSStyleDeclarationValue *values, const char *property,
  const SAC_LexicalUnit *value, SAC_Boolean priority)
{
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyData *propertyData;
  CSSOM_CSSPropertyValue *propertyValue;
  int error;

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return 1;

  propertyData = CSSOM_CSSPropertyData__alloc(value);
  if (propertyData == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return -1;
  }

  propertyValue = CSSOM_CSSPropertyValue__alloc(values->cssom, values, it->hash,
    propertyData, priority, &error);
  if (propertyValue == NULL) {
    CSSOM_CSSPropertyData_release(propertyData);
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return error;
  }

  if (CSSStyleDeclarationValue__addProperty(values, it,
    propertyValue) == NULL)
  {
    CSSOM_CSSPropertyValue_release(propertyValue);
    CSSOM_CSSPropertyData_release(propertyData);
    return -1;
  }

  CSSOM_CSSPropertyData_release(propertyData);

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
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  int priorityLen;

  if (property == NULL) return;
  if (value == NULL) {
    CSSOM_CSSStyleDeclarationValue_removeProperty(values, property);
    return;
  }

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, property, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  if (priority == NULL) {
    priorityLen = 0;
  } else {
    priorityLen = strlen(priority);
  }
  propertyValue = CSSOM__parsePropertyValue(values->cssom, values, it->hash,
    value, strlen(value), priority, priorityLen);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (CSSStyleDeclarationValue__addProperty(values, it,
    propertyValue) == NULL)
  {
    CSSOM_CSSPropertyValue_release(propertyValue);
    return;
  }
}



static void CSSStyleDeclarationValue__fremoveProperty(
  CSSOM_CSSStyleDeclarationValue *values, CSSOM_CSSPropertyType property)
{
  CSSOM_FSMIter_CSSPropertyValue match;
  
  match = CSSOM_FSM_CSSPropertyValue_ffind(values->fsm, property);
  if (match == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  CSSStyleDeclarationValue__eraseProperty(values, match);
}



void CSSOM_CSSStyleDeclarationValue__fsetProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  CSSOM_CSSPropertyType property, const char *value)
{
  CSSOM_FSMIter_CSSPropertyValue it;
  CSSOM_CSSPropertyValue *propertyValue;
  const char *sproperty;

  if (value == NULL) {
    CSSStyleDeclarationValue__fremoveProperty(values, property);
    return;
  }

  sproperty = CSSOM__propertySetting(values->cssom, property)->name;

  it = CSSOM_FSM_CSSPropertyValue_insert(values->fsm, sproperty, NULL);
  if (it == CSSOM_FSM_CSSPropertyValue_end(values->fsm)) return;

  propertyValue = CSSOM__parsePropertyValue(values->cssom, values, it->hash,
    value, strlen(value), NULL, 0);
  if (propertyValue == NULL) {
    if (it->value == NULL) CSSOM_FSM_CSSPropertyValue_erase(values->fsm, it);
    return;
  }

  if (CSSStyleDeclarationValue__addProperty(values, it,
    propertyValue) == NULL)
  {
    CSSOM_CSSPropertyValue_release(propertyValue);
    return;
  }
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

  CSSStyleDeclarationValue__eraseProperty(values, match);

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
