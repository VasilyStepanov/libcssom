#ifndef CSSOM_STYLE_SHEET_H
#define CSSOM_STYLE_SHEET_H

#include <cssom/types.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_StyleSheet CSSOM_StyleSheet;

CSSOM_DOMString CSSOM_StyleSheet_get_type(CSSOM_StyleSheet *styleSheet);



#ifdef __cplusplus
}
#endif

#endif
