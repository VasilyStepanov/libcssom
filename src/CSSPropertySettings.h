#ifndef _CSSOM_CSS_PROPERTY_SETTINGS_H
#define _CSSOM_CSS_PROPERTY_SETTINGS_H

#include "CSSPropertyType.h"
#include "LexicalUnitRange.h"

#include <cssom/typedefs.h>

#include <sacc.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef const SAC_LexicalUnit**(*_CSSOM_PropertyHandler)(
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



struct _CSSOM_CSSPropertySetting {
  const char *name;
  int (*emit)(const CSSOM_CSSPropertyValue *property, FILE *out);
  const CSSOM_CSSPropertyType *subtypes;
  size_t nsubtypes;
  _CSSOM_PropertyHandler handler;
};



extern const struct _CSSOM_CSSPropertySetting CSSOM_propertySettings[];



#ifdef __cplusplus
}
#endif

#endif
