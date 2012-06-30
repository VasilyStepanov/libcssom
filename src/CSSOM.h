#ifndef _CSSOM_CSSOM_H
#define _CSSOM_CSSOM_H

#include <cssom/CSSOM.h>

#include "CSSPropertySetting.h"
#include "MediaQuery.h"
#include "FSM_CSSPropertyValue.h"

#ifdef __cplusplus
extern "C" {
#endif



extern const struct _CSSOM_CSSPropertySetting CSSOM_propertySettings[];

void CSSOM_acquire(CSSOM *cssom);

void CSSOM_release(CSSOM *cssom);

CSSOM_CSSRule* CSSOM__parseRule(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, CSSOM_CSSStyleSheet *styleSheet,
  const char *cssText, int len);

CSSOM_CSSStyleDeclaration* CSSOM__parseStyleDeclaration(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *cssText, int len);

CSSOM_MediaList* CSSOM__parseMedia(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *mediaText, int len);

CSSOM_MediaQuery* CSSOM__parseMediaQuery(const CSSOM *cssom,
  CSSOM_MediaList *parentMedia, const char *mediaText, int len);

CSSOM_Selector* CSSOM__parseSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len);

CSSOM_Selector* CSSOM__parsePageSelector(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const char *selectorText, int len);

int CSSOM__parsePriority(const CSSOM *cssom, const char *priority, int len);

CSSOM_CSSPropertyValue* CSSOM__parsePropertyValue(const CSSOM *cssom,
  CSSOM_CSSStyleDeclarationValue *values, int hash, const char *value,
  int valueLen, const char *important, int importantLen);

void CSSOM__invalidModificationErr(const CSSOM *cssom);

void CSSOM__hierarchyRequestErr(const CSSOM *cssom);

void CSSOM__indexSizeErr(const CSSOM *cssom);

int CSSOM__error(const CSSOM *cssom, const SAC_Error *error);

const CSSOM_FSMTable_CSSPropertyValue* CSSOM__table(const CSSOM *cssom);

const struct _CSSOM_CSSPropertySetting* CSSOM__propertySetting(
  const CSSOM *cssom, int hash);

size_t CSSOM__nproperties(const CSSOM *cssom);

size_t CSSOM__nshorthands(const CSSOM *cssom);



#ifdef __cplusplus
}
#endif

#endif
