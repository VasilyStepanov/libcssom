#include "test_Deque.h"

#include "src/Deque.h"
#include "src/Deque.c"

#include <assert.h>



CSSOM_DEQUE_DECLARE(int, Int)

CSSOM_DEQUE_DEFINE(int, Int)



static void test_Deque_basics() {
  CSSOM_Deque_Int *d;
  CSSOM_DequeIter_Int it;

  d = CSSOM_Deque_Int_alloc(2);

  assert(CSSOM_Deque_Int_size(d) == 2);



  it = CSSOM_Deque_Int_begin(d);
  assert(it != CSSOM_Deque_Int_end(d));
  *it = 1;

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  *it = 2;

  it = CSSOM_DequeIter_Int_next(it);
  assert(it == CSSOM_Deque_Int_end(d));



  it = CSSOM_Deque_Int_begin(d);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 1);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 2);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it == CSSOM_Deque_Int_end(d));



  it = CSSOM_Deque_Int_at(d, 0);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 1);

  it = CSSOM_Deque_Int_at(d, 1);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 2);

  CSSOM_Deque_Int_free(d);
}



static void test_Deque_append() {
  CSSOM_Deque_Int *d;
  CSSOM_DequeIter_Int it;

  d = CSSOM_Deque_Int_alloc(2);

  *CSSOM_Deque_Int_at(d, 0) = 1;
  *CSSOM_Deque_Int_at(d, 1) = 2;

  it = CSSOM_Deque_Int_append(d, 3);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 3);
  assert(CSSOM_Deque_Int_size(d) == 3);

  it = CSSOM_Deque_Int_append(d, 4);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 4);
  assert(CSSOM_Deque_Int_size(d) == 4);



  it = CSSOM_Deque_Int_begin(d);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 1);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 2);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 3);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 4);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it == CSSOM_Deque_Int_end(d));



  CSSOM_Deque_Int_free(d);
}



static void test_Deque_insert() {
  CSSOM_Deque_Int *d;
  CSSOM_DequeIter_Int it;

  d = CSSOM_Deque_Int_alloc(2);

  *CSSOM_Deque_Int_at(d, 0) = 1;
  *CSSOM_Deque_Int_at(d, 1) = 3;

  it = CSSOM_Deque_Int_insert(d, CSSOM_Deque_Int_at(d, 1), 2);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 2);
  assert(CSSOM_Deque_Int_size(d) == 3);

  it = CSSOM_Deque_Int_insert(d, CSSOM_Deque_Int_end(d), 4);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 4);
  assert(CSSOM_Deque_Int_size(d) == 4);



  it = CSSOM_Deque_Int_begin(d);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 1);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 2);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 3);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it != CSSOM_Deque_Int_end(d));
  assert(*it == 4);

  it = CSSOM_DequeIter_Int_next(it);
  assert(it == CSSOM_Deque_Int_end(d));



  CSSOM_Deque_Int_free(d);
}



void test_Deque() {
  test_Deque_basics();
  test_Deque_append();
  test_Deque_insert();
}
