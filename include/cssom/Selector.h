#ifndef CSSOM_SELECTOR_H
#define CSSOM_SELECTOR_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'Selector.idl'
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



#ifdef __cplusplus
}
#endif

#endif
