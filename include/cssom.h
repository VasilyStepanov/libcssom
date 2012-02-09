#ifndef CSSOM_H
#define CSSOM_H

#ifdef __cplusplus
extern "C" {
#endif


typedef const char* CSSOM_DOMString;



/**
 * CSSRule.
 */

typedef struct _CSSOM_CSSRule CSSOM_CSSRule;

unsigned short CSSOM_CSSRule_get_type(CSSOM_CSSRule *cssRule);



/**
 * CSSRuleList.
 */

typedef CSSOM_CSSRule* CSSOM_CSSRuleList;



/**
 * StyleSheet.
 */

typedef struct _CSSOM_StyleSheet CSSOM_StyleSheet;

CSSOM_DOMString CSSOM_StyleSheet_get_type(CSSOM_StyleSheet *styleSheet);



/**
 * CSSStyleSheet.
 */

typedef struct _CSSOM_CSSStyleSheet CSSOM_CSSStyleSheet;

const CSSOM_CSSRuleList*
CSSOM_CSSStyleSheet_get_cssRules(CSSOM_CSSStyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
