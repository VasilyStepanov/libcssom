#include "CSSRule.h"
#include <cssom/CSSRule.h>

#include <stdlib.h>



struct _CSSOM_CSSRule {
  int dummy;
};



void CSSOM_CSSRule_free(CSSOM_CSSRule *cssRule) {
  free(cssRule);
}