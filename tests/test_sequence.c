#include "test_sequence.h"

#include "src/sequence_define.h"

#include <cssom/sequence.h>



CSSOM_SEQUENCE_DECLARE(vi, int)

CSSOM_SEQUENCE_DEFINE(vi, int)




void test_sequence() {
  vi *v = vi_init();
  vi_free(v);
}
