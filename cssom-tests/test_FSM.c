#include "test_FSM.h"

#include "cssom-src/FSM.h"
#include "cssom-src/FSM.c"

#include "test_utils.h"

#include <stdlib.h>
#include <assert.h>



CSSOM_FSM_DECLARE(int, Int)

CSSOM_FSM_DEFINE(int, Int)



static void test_FSM_add() {
  const char *map[] = {
    "a",
    "b",
    "c",
    "d",
    NULL
  };

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);

  fsm = CSSOM_FSM_Int_alloc(table);

  it = CSSOM_FSM_Int_add(fsm, "a", 1);
  assert(it->value == 1);
  it = CSSOM_FSM_Int_add(fsm, "b", 2);
  assert(it->value == 2);

  assert(CSSOM_FSM_Int_size(fsm) == 2);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  it = CSSOM_FSM_Int_find(fsm, "a");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSM_Int_find(fsm, "b");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSM_Int_find(fsm, "c");
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_find(fsm, "d");
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_find(fsm, "x");
  assert(it == CSSOM_FSM_Int_end(fsm));



  it = CSSOM_FSM_Int_add(fsm, "c", 3);
  assert(it->value == 3);
  it = CSSOM_FSM_Int_add(fsm, "d", 4);
  assert(it->value == 4);
  assert(CSSOM_FSM_Int_size(fsm) == 4);

  it = CSSOM_FSM_Int_find(fsm, "a");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSM_Int_find(fsm, "b");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSM_Int_find(fsm, "c");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 3);
  it = CSSOM_FSM_Int_find(fsm, "d");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 4);
  it = CSSOM_FSM_Int_find(fsm, "x");
  assert(it == CSSOM_FSM_Int_end(fsm));

  CSSOM_FSM_Int_free(fsm);

  CSSOM_FSMTable_Int_free(table);
}



static void test_FSM_iterate() {
  const char *map[] = {
    "a",
    "b",
    "c",
    "d",
    NULL
  };

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);

  fsm = CSSOM_FSM_Int_alloc(table);

  CSSOM_FSM_Int_add(fsm, "a", 1);
  CSSOM_FSM_Int_add(fsm, "b", 2);
  CSSOM_FSM_Int_add(fsm, "c", 3);
  CSSOM_FSM_Int_add(fsm, "d", 4);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "a");
  assert(it->hash == 0);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "b");
  assert(it->hash == 1);
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "c");
  assert(it->hash == 2);
  assert(it->value == 3);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "d");
  assert(it->hash == 3);
  assert(it->value == 4);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));

  CSSOM_FSM_Int_free(fsm);

  CSSOM_FSMTable_Int_free(table);
}



static void test_FSM_ffind() {
  const char *map[] = {
    "a",
    "b",
    "c",
    "d",
    NULL
  };
  const int a = 0;
  const int b = 1;
  const int c = 2;
  const int d = 3;

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);

  fsm = CSSOM_FSM_Int_alloc(table);



  it = CSSOM_FSM_Int_ffind(fsm, a);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, b);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, c);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, d);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_add(fsm, "a", 1);
  CSSOM_FSM_Int_add(fsm, "b", 2);
  CSSOM_FSM_Int_add(fsm, "c", 3);
  CSSOM_FSM_Int_add(fsm, "d", 4);



  it = CSSOM_FSM_Int_ffind(fsm, a);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "a");
  assert(it->hash == 0);
  assert(it->value == 1);
  CSSOM_FSM_Int_erase(fsm, it);
  it = CSSOM_FSM_Int_ffind(fsm, b);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "b");
  assert(it->hash == 1);
  assert(it->value == 2);
  CSSOM_FSM_Int_erase(fsm, it);
  it = CSSOM_FSM_Int_ffind(fsm, c);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "c");
  assert(it->hash == 2);
  assert(it->value == 3);
  CSSOM_FSM_Int_erase(fsm, it);
  it = CSSOM_FSM_Int_ffind(fsm, d);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS(it->key, "d");
  assert(it->hash == 3);
  assert(it->value == 4);
  CSSOM_FSM_Int_erase(fsm, it);



  it = CSSOM_FSM_Int_ffind(fsm, a);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, b);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, c);
  assert(it == CSSOM_FSM_Int_end(fsm));
  it = CSSOM_FSM_Int_ffind(fsm, d);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_free(fsm);

  CSSOM_FSMTable_Int_free(table);
}



static void test_FSM_order() {
  const char *map[] = {
    "a",
    "b",
    "c",
    "d",
    NULL
  };

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);

  fsm = CSSOM_FSM_Int_alloc(table);

  CSSOM_FSM_Int_add(fsm, "d", 4);
  CSSOM_FSM_Int_add(fsm, "c", 3);
  CSSOM_FSM_Int_add(fsm, "b", 2);
  CSSOM_FSM_Int_add(fsm, "a", 1);

  /**
   * d c b a
   * 4 3 2 1
   */
  assert(CSSOM_FSM_Int_size(fsm) == 4);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 4);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 3);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_add(fsm, "c", 30);

  /**
   * d b a c
   * 4 2 1 30
   */
  assert(CSSOM_FSM_Int_size(fsm) == 4);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 4);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 30);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_add(fsm, "c", 300);

  /**
   * d b a c
   * 4 2 1 300
   */
  assert(CSSOM_FSM_Int_size(fsm) == 4);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 4);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 300);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  it = CSSOM_FSM_Int_find(fsm, "a");
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 1);
  it = CSSOM_FSM_Int_erase(fsm, it);
  assert(it->value == 300);

  /**
   * d b c
   * 4 2 300
   */
  assert(CSSOM_FSM_Int_size(fsm) == 3);

  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 4);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  assert(it->value == 300);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));

  CSSOM_FSM_Int_free(fsm);

  CSSOM_FSMTable_Int_free(table);
}



static void test_FSM_erase_first() {
  const char *map[] = {
    "background",
    "background-color",
    "background-style",
    NULL
  };

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);
  fsm = CSSOM_FSM_Int_alloc(table);



  CSSOM_FSM_Int_add(fsm, "Background-Color", 1);

  assert(CSSOM_FSM_Int_size(fsm) == 1);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background-color", it->key);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_add(fsm, "Background", 2);

  assert(CSSOM_FSM_Int_size(fsm) == 2);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background-color", it->key);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background", it->key);
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  it = CSSOM_FSM_Int_find(fsm, "BACKGROUND-COLOR");
  assert(it != CSSOM_FSM_Int_end(fsm));
  CSSOM_FSM_Int_erase(fsm, it);

  assert(CSSOM_FSM_Int_size(fsm) == 1);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background", it->key);
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_free(fsm);
  CSSOM_FSMTable_Int_free(table);
}



static void test_FSM_erase_last() {
  const char *map[] = {
    "background",
    "background-color",
    "background-style",
    NULL
  };

  CSSOM_FSMTable_Int *table;
  CSSOM_FSM_Int *fsm;
  CSSOM_FSMIter_Int it;

  table = CSSOM_FSMTable_Int_alloc(map, NULL);
  fsm = CSSOM_FSM_Int_alloc(table);



  CSSOM_FSM_Int_add(fsm, "Background-Color", 1);

  assert(CSSOM_FSM_Int_size(fsm) == 1);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background-color", it->key);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_add(fsm, "Background", 2);

  assert(CSSOM_FSM_Int_size(fsm) == 2);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background-color", it->key);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background", it->key);
  assert(it->value == 2);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  it = CSSOM_FSM_Int_find(fsm, "BACKGROUND");
  assert(it != CSSOM_FSM_Int_end(fsm));
  CSSOM_FSM_Int_erase(fsm, it);

  assert(CSSOM_FSM_Int_size(fsm) == 1);
  it = CSSOM_FSM_Int_begin(fsm);
  assert(it != CSSOM_FSM_Int_end(fsm));
  ASSERT_EQUAL_STRINGS("background-color", it->key);
  assert(it->value == 1);
  it = CSSOM_FSMIter_Int_next(it);
  assert(it == CSSOM_FSM_Int_end(fsm));



  CSSOM_FSM_Int_free(fsm);
  CSSOM_FSMTable_Int_free(table);
}



void test_FSM() {
  test_FSM_add();
  test_FSM_iterate();
  test_FSM_ffind();
  test_FSM_order();
  test_FSM_erase_first();
  test_FSM_erase_last();
}
