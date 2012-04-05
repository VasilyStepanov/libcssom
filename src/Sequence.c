#include "Sequence.h"

#include "Deque_void.h"
#include "memory.h"

#include <assert.h>



struct _CSSOM_Sequence {
  CSSOM_Deque_void *data;
  void (*releaseItem)(void*);
};



CSSOM_Sequence* CSSOM_Sequence__alloc(void (*releaseItem)(void*)) {
  CSSOM_Deque_void *data;
  CSSOM_Sequence *sequence;

  data = CSSOM_Deque_void_alloc(0);
  if (data == NULL) return NULL;

  sequence = (CSSOM_Sequence*)CSSOM_malloc(sizeof(CSSOM_Sequence));
  if (sequence == NULL) {
    CSSOM_Deque_void_free(data);
    return NULL;
  }

  sequence->data = data;
  sequence->releaseItem = releaseItem;

  return sequence;
}



void CSSOM_Sequence__free(CSSOM_Sequence *sequence) {
  CSSOM_DequeIter_void it;

  for (it = CSSOM_Deque_void_begin(sequence->data);
    it != CSSOM_Deque_void_end(sequence->data);
    it = CSSOM_DequeIter_void_next(it))
  {
    sequence->releaseItem(*it);
  }

  CSSOM_Deque_void_free(sequence->data);
  CSSOM_free(sequence);
}



void* CSSOM_Sequence__append(CSSOM_Sequence *sequence, void *ptr) {
  CSSOM_DequeIter_void it;

  it = CSSOM_Deque_void_append(sequence->data, ptr);
  if (it == CSSOM_Deque_void_end(sequence->data)) return NULL;

  return *it;
}



size_t CSSOM_Sequence_size(const CSSOM_Sequence *sequence) {
  return CSSOM_Deque_void_size(sequence->data);
}



void* CSSOM_Sequence_at(const CSSOM_Sequence *sequence, size_t index) {
  return *CSSOM_Deque_void_at(sequence->data, index);
}
