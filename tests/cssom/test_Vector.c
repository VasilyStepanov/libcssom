#include "test_Vector.h"

#include "src/Vector.h"
#include "src/Vector.c"

#include <assert.h>



CSSOM_VECTOR_DECLARE(int, Int)

CSSOM_VECTOR_DEFINE(int, Int)



void test_Vector_basics(void) {
  CSSOM_Vector_Int *v;
  CSSOM_VectorIter_Int it;
  CSSOM_VectorConstIter_Int cit;

  v = CSSOM_Vector_Int_alloc(2);

  assert(CSSOM_Vector_Int_size(v) == 2);



  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 2;

  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);



  it = CSSOM_Vector_Int_begin(v);
  assert(it != CSSOM_Vector_Int_end(v));
  assert(*it == 1);

  it = CSSOM_VectorIter_Int_next(it);
  assert(it != CSSOM_Vector_Int_end(v));
  assert(*it == 2);

  it = CSSOM_VectorIter_Int_next(it);
  assert(it == CSSOM_Vector_Int_end(v));



  cit = CSSOM_Vector_Int_cbegin(v);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 1);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 2);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit == CSSOM_Vector_Int_cend(v));



  CSSOM_Vector_Int_free(v);
}



void test_Vector_append(void) {
  CSSOM_Vector_Int *v;
  CSSOM_VectorConstIter_Int cit;

  v = CSSOM_Vector_Int_alloc_ex(2, 4);

  assert(CSSOM_Vector_Int_size(v) == 2);
  assert(CSSOM_Vector_Int_capacity(v) == 4);



  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 2;

  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);



  CSSOM_Vector_Int_append(v, 3);
  CSSOM_Vector_Int_append(v, 4);

  assert(CSSOM_Vector_Int_size(v) == 4);
  assert(CSSOM_Vector_Int_capacity(v) == 4);
  assert(CSSOM_Vector_Int_begin(v)[2] == 3);
  assert(CSSOM_Vector_Int_begin(v)[3] == 4);



  CSSOM_Vector_Int_append(v, 5);
  CSSOM_Vector_Int_append(v, 6);
  CSSOM_Vector_Int_append(v, 7);

  assert(CSSOM_Vector_Int_size(v) == 7);
  assert(CSSOM_Vector_Int_capacity(v) >= 7);
  assert(CSSOM_Vector_Int_begin(v)[4] == 5);
  assert(CSSOM_Vector_Int_begin(v)[5] == 6);
  assert(CSSOM_Vector_Int_begin(v)[6] == 7);



  cit = CSSOM_Vector_Int_cbegin(v);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 1);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 2);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 3);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 4);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 5);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 6);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit != CSSOM_Vector_Int_cend(v));
  assert(*cit == 7);

  cit = CSSOM_VectorConstIter_Int_next(cit);
  assert(cit == CSSOM_Vector_Int_cend(v));



  CSSOM_Vector_Int_free(v);
}



void test_Vector_insert(void) {
  CSSOM_Vector_Int *v;
  CSSOM_VectorIter_Int it;

  v = CSSOM_Vector_Int_alloc(2);

  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 3;

  assert(CSSOM_Vector_Int_size(v) == 2);


  it = CSSOM_Vector_Int_begin(v) + 1;

  assert(*it == 3);



  it = CSSOM_Vector_Int_insert(v, it, 2);

  assert(*it == 2);
  assert(CSSOM_Vector_Int_size(v) == 3);



  it = CSSOM_Vector_Int_insert(v, CSSOM_Vector_Int_end(v), 4);

  assert(CSSOM_Vector_Int_size(v) == 4);
  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);
  assert(CSSOM_Vector_Int_begin(v)[2] == 3);
  assert(CSSOM_Vector_Int_begin(v)[3] == 4);



  CSSOM_Vector_Int_free(v);
}



void test_Vector_erase(void) {
  CSSOM_Vector_Int *v;
  CSSOM_VectorIter_Int it;

  v = CSSOM_Vector_Int_alloc(3);

  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 100;
  CSSOM_Vector_Int_begin(v)[2] = 2;

  assert(CSSOM_Vector_Int_size(v) == 3);


  it = CSSOM_Vector_Int_begin(v) + 1;

  assert(*it == 100);



  it = CSSOM_Vector_Int_erase(v, it);

  assert(*it == 2);
  assert(CSSOM_Vector_Int_size(v) == 2);

  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);


  it = CSSOM_Vector_Int_erase(v, it);

  assert(CSSOM_Vector_Int_size(v) == 1);
  assert(it == CSSOM_Vector_Int_end(v));
  assert(CSSOM_Vector_Int_begin(v)[0] == 1);



  CSSOM_Vector_Int_free(v);
}



void test_Vector_pop(void) {
  CSSOM_Vector_Int *v;

  v = CSSOM_Vector_Int_alloc(3);

  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 2;
  CSSOM_Vector_Int_begin(v)[2] = 3;

  assert(CSSOM_Vector_Int_size(v) == 3);



  CSSOM_Vector_Int_pop(v);

  assert(CSSOM_Vector_Int_size(v) == 2);
  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);



  CSSOM_Vector_Int_pop(v);

  assert(CSSOM_Vector_Int_size(v) == 1);
  assert(CSSOM_Vector_Int_begin(v)[0] == 1);



  CSSOM_Vector_Int_pop(v);

  assert(CSSOM_Vector_Int_size(v) == 0);



  CSSOM_Vector_Int_free(v);
}



void test_Vector(void) {
  test_Vector_basics();
  test_Vector_append();
  test_Vector_insert();
  test_Vector_erase();
  test_Vector_pop();
}
