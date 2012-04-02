#ifndef CSSOM_CSSOM_H
#define CSSOM_CSSOM_H

#include <cssom/CSSStyleSheet.h>

#include <sacc.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM CSSOM;



CSSOM * CSSOM_create(const char * * properties);

void CSSOM_acquire(CSSOM * cssom);

void CSSOM_release(CSSOM * cssom);

void * CSSOM_getUserData(const CSSOM * cssom);

void CSSOM_setUserData(CSSOM * cssom, void * userData);

void CSSOM_setErrorHandler(CSSOM * cssom, SAC_ErrorHandler handler);

void CSSOM_setFatalErrorHandler(CSSOM * cssom, SAC_FatalErrorHandler handler);

CSSOM_CSSStyleSheet * CSSOM_parseStyleSheet(const CSSOM *cssom,
  const char * cssText, int len);



#ifdef __cplusplus
}
#endif

#endif
