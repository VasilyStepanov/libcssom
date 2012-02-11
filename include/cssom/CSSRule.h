#ifndef CSSOM_CSSRULE_H
#define CSSOM_CSSRULE_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_CSSRule CSSOM_CSSRule;



void CSSOM_CSSRule_free(CSSOM_CSSRule *cssRule);

unsigned short CSSOM_CSSRule_type(CSSOM_CSSRule *cssRule);



#ifdef __cplusplus
}
#endif

#endif
