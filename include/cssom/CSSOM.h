#ifndef CSSOM_CSSOM_H
#define CSSOM_CSSOM_H

#include <cssom/typedefs.h>

#include <sacc.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef enum {
  CSSOM_FATAL_ERROR_NO_MEMORY = SAC_FATAL_ERROR_NO_MEMORY
} CSSOM_FatalErrorCode;

typedef struct {
  signed int line;   /* -1 if unknown */
  signed int column; /* -1 if unknown */
  CSSOM_FatalErrorCode code;
} CSSOM_FatalError;

typedef void (*CSSOM_FatalErrorHandler)(void *userData,
  const CSSOM_FatalError *error);



typedef enum {
  CSSOM_ERROR_NOT_SUPPORTED = SAC_ERROR_NOT_SUPPORTED,
  CSSOM_ERROR_SYNTAX = SAC_ERROR_SYNTAX,
  CSSOM_ERROR_INVALID_MODIFICATION_ERR = 1,
  CSSOM_ERROR_INDEX_SIZE_ERR = 2
} CSSOM_ErrorCode;

typedef struct {
  signed int line;   /* -1 if unknown */
  signed int column; /* -1 if unknown */
  CSSOM_ErrorCode code;
  const char * data; /* NULL if it is not relevant */
} CSSOM_Error;

typedef int (*CSSOM_ErrorHandler)(void *userData,
  const CSSOM_Error *error);



CSSOM * CSSOM_create(const char * * properties);

void CSSOM_acquire(CSSOM * cssom);

void CSSOM_release(CSSOM * cssom);

void * CSSOM_getUserData(const CSSOM * cssom);

void CSSOM_setUserData(CSSOM * cssom, void * userData);

void CSSOM_setErrorHandler(CSSOM * cssom, CSSOM_ErrorHandler handler);

void CSSOM_setFatalErrorHandler(CSSOM * cssom, CSSOM_FatalErrorHandler handler);

CSSOM_CSSStyleSheet * CSSOM_parse(const CSSOM *cssom,
  const char * cssText, int len);



#ifdef __cplusplus
}
#endif

#endif
