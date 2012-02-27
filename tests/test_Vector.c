#include "test_Vector.h"

#include "src/Vector.h"
#include "src/Vector.c"

#include <assert.h>



CSSOM_VECTOR_DECLARE(int, Int)

CSSOM_VECTOR_DEFINE(int, Int)



void test_Vector_basics() {
  CSSOM_Vector_Int *v;
  CSSOM_VectorIter_Int it;
  CSSOM_VectorConstIter_Int cit;

  v = CSSOM_Vector_Int_alloc(2);

  CSSOM_Vector_Int_begin(v)[0] = 1;
  CSSOM_Vector_Int_begin(v)[1] = 2;



  assert(CSSOM_Vector_Int_begin(v)[0] == 1);
  assert(CSSOM_Vector_Int_begin(v)[1] == 2);
  assert(CSSOM_Vector_Int_size(v) == 2);



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



void test_Vector() {
  test_Vector_basics();
}
