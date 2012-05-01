#include "CSSStyleDeclarationValue.h"

#include "CSSOM.h"
#include "CSSStyleSheet.h"
#include "FSM_CSSProperty.h"
#include "memory.h"

#include <cssom/CSSStyleDeclaration.h>
#include <cssom/CSSStyleRule.h>

#include <assert.h>



struct _CSSOM_CSSStyleDeclarationValue {
  size_t handles;
  CSSOM_CSSStyleDeclaration *ownerStyle;
  CSSOM_FSM_CSSProperty *fsm;
};



CSSOM_CSSStyleDeclarationValue* CSSOM_CSSStyleDeclarationValue__alloc(
  CSSOM_CSSStyleDeclaration *ownerStyle)
{
  const CSSOM_FSMTable_CSSProperty *table;
  CSSOM_CSSStyleDeclarationValue *values;
  CSSOM_FSM_CSSProperty *fsm;

  table = CSSOM__table(
    CSSOM_CSSStyleSheet__cssom(
      CSSOM_CSSRule_parentStyleSheet(
        CSSOM_CSSStyleDeclaration_parentRule(ownerStyle))));

  fsm = CSSOM_FSM_CSSProperty_alloc(table);
  if (fsm == NULL) return NULL;

  values = (CSSOM_CSSStyleDeclarationValue*)CSSOM_malloc(
    sizeof(CSSOM_CSSStyleDeclarationValue));
  if (values == NULL) {
    CSSOM_FSM_CSSProperty_free(fsm);
    return NULL;
  }

  values->handles = 1;
  values->ownerStyle = ownerStyle;
  values->fsm = fsm;

  return values;
}



void CSSOM_CSSStyleDeclarationValue_acquire(
  CSSOM_CSSStyleDeclarationValue *values)
{
  if (values == NULL) return;

  ++values->handles;
  CSSOM_CSSStyleDeclaration_acquire(values->ownerStyle);
}



void CSSOM_CSSStyleDeclarationValue_release(
  CSSOM_CSSStyleDeclarationValue *values)
{
  if (values == NULL) return;

  assert(values->handles > 0);
  --values->handles;
  if (values->handles > 0) {
    CSSOM_CSSStyleDeclaration_release(values->ownerStyle);
    return;
  }

  CSSOM_FSM_CSSProperty_free(values->fsm);
  CSSOM_free(values);
}



unsigned long CSSOM_CSSStyleDeclarationValue__length(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSProperty_size(values->fsm);
}



const char* CSSOM_CSSStyleDeclarationValue__item(
  CSSOM_CSSStyleDeclarationValue *values, unsigned long index)
{
  CSSOM_FSMConstIter_CSSProperty match;

  if (index >= CSSOM_FSM_CSSProperty_size(values->fsm)) return NULL;

  match = CSSOM_FSM_CSSProperty_at(values->fsm, index);

  return CSSOM_CSSProperty_name(match->value);
}



const char* CSSOM_CSSStyleDeclarationValue__getPropertyValue(
  const CSSOM_CSSStyleDeclarationValue *values, const char *property)
{
  CSSOM_FSMIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_find(values->fsm, property);
  if (it == CSSOM_FSM_CSSProperty_end(values->fsm)) return NULL;

  return CSSOM_CSSProperty_cssText(it->value);
}



const char* CSSOM_CSSStyleDeclarationValue__getPropertyPriority(
  const CSSOM_CSSStyleDeclarationValue *values, const char * property)
{
  CSSOM_FSMIter_CSSProperty it;

  it = CSSOM_FSM_CSSProperty_find(values->fsm, property);
  if (it == CSSOM_FSM_CSSProperty_end(values->fsm)) return "";

  if (CSSOM_CSSProperty_important(it->value) == 0) return "";

  return "important";
}



CSSOM_CSSProperty* CSSOM_CSSStyleDeclarationValue__setProperty(
  CSSOM_CSSStyleDeclarationValue *values,
  const char *property, const SAC_LexicalUnit *value, SAC_Boolean important)
{
  CSSOM_CSSProperty *prop;
  CSSOM_FSMIter_CSSProperty it;

  prop = CSSOM_CSSProperty__alloc(value, important);
  if (prop == NULL) return NULL;

  it = CSSOM_FSM_CSSProperty_add(values->fsm, property, prop);
  if (it == CSSOM_FSM_CSSProperty_end(values->fsm)) {
    CSSOM_CSSProperty_release(prop);
    return NULL;
  }

  CSSOM_CSSProperty__setName(prop, it->key);

  return prop;
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValueValue__begin(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSProperty_begin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter CSSOM_CSSStyleDeclarationValue__end(
  CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSProperty_end(values->fsm);
}



CSSOM_CSSStyleDeclarationValueIter
CSSOM_CSSStyleDeclarationValueIter_next(
  CSSOM_CSSStyleDeclarationValueIter iter)
{
  return CSSOM_FSMIter_CSSProperty_next(iter);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cbegin(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSProperty_cbegin(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter CSSOM_CSSStyleDeclarationValue__cend(
  const CSSOM_CSSStyleDeclarationValue *values)
{
  return CSSOM_FSM_CSSProperty_cend(values->fsm);
}



CSSOM_CSSStyleDeclarationValueConstIter
CSSOM_CSSStyleDeclarationValueConstIter_next(
  CSSOM_CSSStyleDeclarationValueConstIter iter)
{
  return CSSOM_FSMConstIter_CSSProperty_next(iter);
}




