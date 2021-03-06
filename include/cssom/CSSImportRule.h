#ifndef CSSOM_CSS_IMPORT_RULE_H
#define CSSOM_CSS_IMPORT_RULE_H



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSRule.idl'
 */



#include <cssom/typedefs.h>

#include <cssom/CSSRule.h>

#ifdef __cplusplus
extern "C" {
#endif



#define CSSOM_CSSImportRule_acquire(cssImportRule) \
  CSSOM_CSSRule_acquire((CSSOM_CSSRule*)(cssImportRule))



#define CSSOM_CSSImportRule_release(cssImportRule) \
  CSSOM_CSSRule_release((CSSOM_CSSRule*)(cssImportRule))



const char * CSSOM_CSSImportRule_href(const CSSOM_CSSImportRule * cssImportRule);



CSSOM_MediaList* CSSOM_CSSImportRule_media(const CSSOM_CSSImportRule * cssImportRule);



void CSSOM_CSSImportRule_setMedia(CSSOM_CSSImportRule * cssImportRule, const char * media);



#ifdef __cplusplus
}
#endif

#endif
