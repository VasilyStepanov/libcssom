#ifndef CSSOM_SELECTOR_H
#define CSSOM_SELECTOR_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_Selector_acquire(
  CSSOM_Selector * selector);



void CSSOM_Selector_release(
  CSSOM_Selector * selector);



const char * CSSOM_Selector_selectorText(const CSSOM_Selector * selector);



void CSSOM_Selector_setSelectorText(CSSOM_Selector * selector, const char * selectorText);



CSSOM_CSSRule* CSSOM_Selector_parentRule(const CSSOM_Selector * selector);



unsigned long CSSOM_Selector_specificity(const CSSOM_Selector * selector);



void CSSOM_Selector_select(CSSOM_Selector * selector, void * root, void * selection);



#ifdef __cplusplus
}
#endif

#endif
