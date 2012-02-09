#include "test_list.h"

#include "src/list.h"
#include "src/list.c"

#include <assert.h>



CSSOM_LIST_DECLARE(int, Int)

CSSOM_LIST_DEFINE(int, Int)




void test_list() {
  CSSOM_IntList *l;
  CSSOM_IntListIter it;

  l = CSSOM_IntList_alloc();

  assert(CSSOM_IntList_begin(l) == CSSOM_IntList_end(l));
  assert(CSSOM_IntList_size(l) == 0);

  CSSOM_IntList_append(l, 1);
  CSSOM_IntList_append(l, 2);
  CSSOM_IntList_append(l, 3);

  it = CSSOM_IntList_begin(l);
  assert(it != CSSOM_IntList_end(l));
  assert(*it == 1);

  it = CSSOM_IntListIter_next(it);
  assert(it != CSSOM_IntList_end(l));
  assert(*it == 2);

  it = CSSOM_IntListIter_next(it);
  assert(it != CSSOM_IntList_end(l));
  assert(*it == 3);

  it = CSSOM_IntListIter_next(it);
  assert(it == CSSOM_IntList_end(l));

  assert(CSSOM_IntList_size(l) == 3);

  CSSOM_IntList_free(l);
}
