#include "test_sequence.h"

#include "src/sequence_impl.h"

#include <cssom/sequence.h>



CSSOM_SEQUENCE(vi, int)

CSSOM_SEQUENCE_IMPL(vi, int)




void test_sequence() {
  vi *v = vi_init();
  vi_free(v);
}
