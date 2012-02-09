#ifndef CSSOM_SEQUENCE_H
#define CSSOM_SEQUENCE_H

#ifdef __cplusplus
extern "C" {
#endif


#define CSSOM_SEQUENCE(N, T) \
  typedef struct _##N N; \
  \
  N* N##_init(); \
  void N##_free(N *sequence);


#ifdef __cplusplus
}
#endif

#endif
