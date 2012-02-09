#ifndef CSSOM_PARSER_H
#define CSSOM_PARSER_H

#include <cssom/css_style_sheet.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_Parser CSSOM_Parser;

const CSSOM_CSSStyleSheet* parser(CSSOM_Parser *parser, const char *css);



#ifdef __cplusplus
}
#endif

#endif
