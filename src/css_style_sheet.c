#include <cssom.h>

#include <stdlib.h>



void CSSOM_CSSStyleSheet_free(CSSOM_CSSStyleSheet *styleSheet) {
  free(styleSheet);
}
