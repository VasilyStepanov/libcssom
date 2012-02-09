#ifndef CSSOM_SEQUENCE_H
#define CSSOM_SEQUENCE_H

#ifdef __cplusplus
extern "C" {
#endif


#define CSSOM_SEQUENCE(name, type) \
  typedef struct _##name name; \
  \
  void name##_free(name *sequence);


#ifdef __cplusplus
}
#endif

#endif
