#ifndef _CSSOM_SEQUENCE_H
#define _CSSOM_SEQUENCE_H

#include <cssom/Sequence.h>

#ifdef __cplusplus
extern "C" {
#endif



CSSOM_Sequence* CSSOM_Sequence__alloc(void (*releaseItem)(void*));

void CSSOM_Sequence__free(CSSOM_Sequence *sequence);

void* CSSOM_Sequence__append(CSSOM_Sequence *sequence, void *ptr);



#ifdef __cplusplus
}
#endif

#endif
