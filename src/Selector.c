#include "Selector.h"

#include "MediaList.h"
#include "CSSEmitter.h"
#include "memory.h"
#include "gcc.h"

#include <cssom/CSSRule.h>

#include <assert.h>
#include <stdio.h>



struct _CSSOM_Selector {
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSRule *ownerRule;
  char *selectorText;
  const SAC_Selector **selectors;
};



CSSOM_Selector* CSSOM_Selector__alloc(CSSOM_CSSRule *ownerRule,
  const SAC_Selector *selectors[])
{
  CSSOM_Selector *selector;

  selector = (CSSOM_Selector*)CSSOM_malloc(sizeof(CSSOM_Selector));
  if (selector == NULL) return NULL;

  selector->handles = 1;
  selector->parser = NULL;
  selector->ownerRule = ownerRule;
  selector->selectorText = NULL;
  selector->selectors = selectors;

  return selector;
}



void CSSOM_Selector_acquire(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  ++selector->handles;
  CSSOM_CSSRule_acquire(selector->ownerRule);
}



void CSSOM_Selector_release(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  assert(selector->handles > 0);
  --selector->handles;
  if (selector->handles > 0) {
    CSSOM_CSSRule_release(selector->ownerRule);
    return;
  }

  CSSOM_native_free(selector->selectorText);
  SAC_DisposeParser(selector->parser);
  CSSOM_free(selector);
}



CSSOM_CSSRule* CSSOM_Selector__ownerRule(const CSSOM_Selector *selector) {
  return selector->ownerRule;
}



const char* CSSOM_Selector_selectorText(const CSSOM_Selector *selector) {
  if (selector->selectorText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSRule_type(CSSOM_Selector__ownerRule(selector)) !=
      CSSOM_CSSRule_PAGE_RULE)
    {
      if (CSSOM_CSSEmitter_selectors(out, selector->selectors) != 0) {
        fclose(out);
        CSSOM_native_free(buf);
        return NULL;
      }
    } else {
      if (CSSOM_CSSEmitter_pageSelectors(out, selector->selectors) != 0) {
        fclose(out);
        CSSOM_native_free(buf);
        return NULL;
      }
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_Selector*)selector)->selectorText = buf;
  }
  return selector->selectorText;
}



const SAC_Selector** CSSOM_Selector_selectors(const CSSOM_Selector *selector) {
  return selector->selectors;
}



void CSSOM_Selector__keepParser(CSSOM_Selector *selector,
  SAC_Parser parser)
{
  selector->parser = parser;
}
