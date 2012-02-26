#ifndef CSSOM_CSSPROPERTY_H
#define CSSOM_CSSPROPERTY_H

#ifdef __cplusplus
extern "C" {
#endif



typedef enum _CSSOM_CSSPropertyType {
  CSSOM_COLOR_PROPERTY = 0
} CSSOM_CSSPropertyType;

typedef struct _CSSOM_CSSPropertyDef {
  const char *name;
  int type;
} CSSOM_CSSPropertyDef;



extern CSSOM_CSSPropertyDef CSSOM_CSSPropertyDefs[];



#ifdef __cplusplus
}
#endif

#endif
