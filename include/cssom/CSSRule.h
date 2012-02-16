#ifndef CSSOM_CSSRULE_H
#define CSSOM_CSSRULE_H

#ifdef __cplusplus
extern "C" {
#endif



typedef enum _CSSOM_CSSRuleType {
  CSSOM_STYLE_RULE = 1,
  CSSOM_IMPORT_RULE = 3,
  CSSOM_MEDIA_RULE = 4,
  CSSOM_FONT_FACE_RULE = 5,
  CSSOM_PAGE_RULE = 6,
  CSSOM_NAMESPACE_RULE = 10
} CSSOM_CSSRuleType;

typedef struct _CSSOM_CSSRule CSSOM_CSSRule;



CSSOM_CSSRuleType CSSOM_CSSRule_type(const CSSOM_CSSRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
