#include "test_list.h"

#include "src/list.h"

#include <assert.h>



CSSOM_LIST_DECLARE(vi, int)

CSSOM_LIST_DEFINE(vi, int)




void test_list() {
  vi *v = vi_init();
  vi_free(v);
}
