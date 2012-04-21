#ifndef CSSOM_SEQUENCE_H
#define CSSOM_SEQUENCE_H

#include <cssom/typedefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



void CSSOM_Sequence_acquire(CSSOM_Sequence *sequence);

void CSSOM_Sequence_release(CSSOM_Sequence *sequence);

size_t CSSOM_Sequence_size(const CSSOM_Sequence *sequence);

void* CSSOM_Sequence_at(const CSSOM_Sequence *sequence, size_t index);



#ifdef __cplusplus
}
#endif

#endif
