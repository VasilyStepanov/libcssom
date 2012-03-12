#include "test_List.h"

#include "cssom-src/List.h"
#include "cssom-src/List.c"

#include <assert.h>



CSSOM_LIST_DECLARE(int, Int)

CSSOM_LIST_DEFINE(int, Int)



void test_List_basics() {
  CSSOM_List_Int *l;
  CSSOM_ListIter_Int it;
  CSSOM_ListConstIter_Int cit;

  l = CSSOM_List_Int_alloc();

  assert(CSSOM_List_Int_begin(l) == CSSOM_List_Int_end(l));
  assert(CSSOM_List_Int_size(l) == 0);

  CSSOM_List_Int_append(l, 1);
  CSSOM_List_Int_append(l, 2);
  CSSOM_List_Int_append(l, 3);



  it = CSSOM_List_Int_begin(l);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 1);

  *it = 10;
  assert(*CSSOM_List_Int_begin(l) == 10);
  *it = 1;

  it = CSSOM_ListIter_Int_next(it);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 2);

  it = CSSOM_ListIter_Int_next(it);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 3);

  it = CSSOM_ListIter_Int_next(it);
  assert(it == CSSOM_List_Int_end(l));



  cit = CSSOM_List_Int_cbegin(l);
  assert(cit != CSSOM_List_Int_cend(l));
  assert(*cit == 1);

  cit = CSSOM_ListConstIter_Int_next(cit);
  assert(cit != CSSOM_List_Int_cend(l));
  assert(*cit == 2);

  cit = CSSOM_ListConstIter_Int_next(cit);
  assert(cit != CSSOM_List_Int_cend(l));
  assert(*cit == 3);

  cit = CSSOM_ListConstIter_Int_next(cit);
  assert(cit == CSSOM_List_Int_cend(l));



  assert(CSSOM_List_Int_size(l) == 3);

  CSSOM_List_Int_free(l);
}



void test_List_insert() {
  CSSOM_List_Int *l;
  CSSOM_ListIter_Int it;

  l = CSSOM_List_Int_alloc();

  /**
   * [3]
   *  ^
   */
  it = CSSOM_List_Int_insert(l, CSSOM_List_Int_end(l), 3);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 3);

  /**
   * [1, 3]
   *  ^
   */
  it = CSSOM_List_Int_insert(l, it, 1);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 1);

  /**
   * [1, 3]
   *     ^
   */
  it = CSSOM_ListIter_Int_next(it);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 3);

  /**
   * [1, 2, 3]
   *     ^
   */
  it = CSSOM_List_Int_insert(l, it, 2);
  assert(it != CSSOM_List_Int_end(l));
  assert(*it == 2);

  assert(CSSOM_List_Int_size(l) == 3);
  it = CSSOM_List_Int_begin(l);
  assert(*it == 1);
  it = CSSOM_ListIter_Int_next(it);
  assert(*it == 2);
  it = CSSOM_ListIter_Int_next(it);
  assert(*it == 3);
  it = CSSOM_ListIter_Int_next(it);
  assert(it == CSSOM_List_Int_end(l));


  CSSOM_List_Int_free(l);
}



void test_List_erase() {
  CSSOM_List_Int *l;
  CSSOM_ListIter_Int it;

  l = CSSOM_List_Int_alloc();

  /**
   * [1, 2, 3]
   *     ^
   */
  CSSOM_List_Int_append(l, 1);
  it = CSSOM_List_Int_append(l, 2);
  CSSOM_List_Int_append(l, 3);

  /**
   * [1, 3]
   *     ^
   */
  it = CSSOM_List_Int_erase(l, it);
  assert(CSSOM_List_Int_size(l) == 2);
  assert(*it == 3);
  it = CSSOM_List_Int_begin(l);
  assert(*it == 1);
  it = CSSOM_ListIter_Int_next(it);
  assert(*it == 3);
  assert(CSSOM_ListIter_Int_next(it) == CSSOM_List_Int_end(l));

  /**
   * [1]
   *     ^
   */
  it = CSSOM_List_Int_erase(l, it);
  assert(CSSOM_List_Int_size(l) == 1);
  assert(it == CSSOM_List_Int_end(l));
  it = CSSOM_List_Int_begin(l);
  assert(*it == 1);
  it = CSSOM_ListIter_Int_next(it);
  assert(it == CSSOM_List_Int_end(l));

  /**
   * []
   */
  it = CSSOM_List_Int_erase(l, CSSOM_List_Int_begin(l));
  assert(CSSOM_List_Int_size(l) == 0);
  assert(it == CSSOM_List_Int_end(l));
  assert(CSSOM_List_Int_begin(l) == CSSOM_List_Int_end(l));


  CSSOM_List_Int_free(l);
}



void test_List() {
  test_List_basics();
  test_List_insert();
  test_List_erase();
}
