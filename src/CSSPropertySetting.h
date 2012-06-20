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



typedef const SAC_LexicalUnit**(*_CSSOM_PropertyHandler)(const CSSOM *cssom,
  const SAC_LexicalUnit **begin, const SAC_LexicalUnit **end,
  struct _CSSOM_LexicalUnitRange *values);



struct _CSSOM_CSSPropertySetting {
  const char *name;
  const CSSOM_CSSPropertyType *subtypes;
  size_t nsubtypes;
  _CSSOM_PropertyHandler handler;
  int (*omit)(const CSSOM_CSSPropertyValue *property,
    struct _CSSOM_LexicalUnitRange *values);
};



#ifdef __cplusplus
}
#endif

#endif
