#include "CSSPropertyValue.h"

#include "memory.h"

#include <assert.h>



struct _CSSOM_CSSPropertyValue {
  size_t handles;
};



void CSSOM_CSSPropertyValue_acquire(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  ++property->handles;
}



void CSSOM_CSSPropertyValue_release(CSSOM_CSSPropertyValue *property) {
  if (property == NULL) return;

  assert(property->handles > 0);
  --property->handles;
  if (property->handles > 0) return;

  CSSOM_free(property);
}
