#ifndef CSSOM_SEQUENCE_H
#define CSSOM_SEQUENCE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _CSSOM_Sequence CSSOM_Sequence;



size_t CSSOM_Sequence_size(const CSSOM_Sequence *sequence);

void* CSSOM_Sequence_at(const CSSOM_Sequence *sequence, size_t index);



#ifdef __cplusplus
}
#endif

#endif