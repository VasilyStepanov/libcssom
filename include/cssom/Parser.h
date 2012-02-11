#ifndef CSSOM_PARSER_H
#define CSSOM_PARSER_H

#include <cssom/CSSStyleSheet.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_Parser CSSOM_Parser;



/**
 * Create the parser.
 *
 * Returns NULL if out of memory.
 *
 * The caller is responsible for disposing the parser by calling
 * CSSOM_Parser_free().
 */
CSSOM_Parser* CSSOM_Parser_alloc();

/**
 * Release the parser.
 */
void CSSOM_Parser_free(CSSOM_Parser *parser);

/**
 * Parse style sheet.
 *
 * The caller is responsible for disposing the CSSStyleSheet by calling
 * CSSOM_CSSStyleSheet_free().
 */
CSSOM_CSSStyleSheet* CSSOM_Parser_parseStyleSheet(CSSOM_Parser *parser,
  const char *cssText);



#ifdef __cplusplus
}
#endif

#endif
