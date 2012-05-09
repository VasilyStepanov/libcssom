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
  CSSOM_ERROR_INDEX_SIZE_ERR = 2,
  CSSOM_ERROR_HIERARCHY_REQUEST_ERR = 3
} CSSOM_ErrorCode;

typedef struct {
  signed int line;   /* -1 if unknown */
  signed int column; /* -1 if unknown */
  CSSOM_ErrorCode code;
  const char * data; /* NULL if it is not relevant */
} CSSOM_Error;

typedef int (*CSSOM_ErrorHandler)(void *userData,
  const CSSOM_Error *error);



typedef enum {
  CSSOM_TEXT_NODE,
  CSSOM_ELEMENT_NODE
} CSSOM_NodeType;




typedef struct {
  CSSOM_NodeType (*Node_type)(void *node);
  const char * (*Node_name)(void *node);
  const char * (*Node_attribute)(void *node, const char *name);
  const char * (*Node_class)(void *node);
  const char * (*Node_id)(void *node);
  void* (*Node_parent)(void *node);
  void* (*Node_children)(void *node);
  void* (*Node_next)(void *node);
  void (*Selection_append)(void *selection, void *node);
} CSSOM_DOMAPI;



CSSOM * CSSOM_create(const char * * properties);

void CSSOM_acquire(CSSOM * cssom);

void CSSOM_release(CSSOM * cssom);

void * CSSOM_getUserData(const CSSOM * cssom);

void CSSOM_setUserData(CSSOM * cssom, void * userData);

const CSSOM_DOMAPI* CSSOM_getDOMAPI(const CSSOM * cssom);

void CSSOM_setDOMAPI(CSSOM * cssom, const CSSOM_DOMAPI *domapi);

void CSSOM_setErrorHandler(CSSOM * cssom, CSSOM_ErrorHandler handler);

void CSSOM_setFatalErrorHandler(CSSOM * cssom, CSSOM_FatalErrorHandler handler);

CSSOM_CSSStyleSheet * CSSOM_parse(const CSSOM *cssom,
  const char * cssText, int len);

CSSOM_Selector * CSSOM_parseSelector(const CSSOM *cssom,
  const char * selectorText, int len);



#ifdef __cplusplus
}
#endif

#endif
