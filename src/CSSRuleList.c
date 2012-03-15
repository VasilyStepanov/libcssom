#include "CSSRuleList.h"

#include "Deque_CSSRule.h"
#include "CSSRule.h"

#include <stdlib.h>
#include <assert.h>



struct _CSSOM_CSSRuleList {
  size_t handles;
  CSSOM_Deque_CSSRule *data;
};



CSSOM_CSSRuleList* CSSOM_CSSRuleList__alloc() {
  CSSOM_Deque_CSSRule *data;
  CSSOM_CSSRuleList *cssRules;

  data = CSSOM_Deque_CSSRule_alloc(0);
  if (data == NULL) return NULL;

  cssRules = (CSSOM_CSSRuleList*)malloc(sizeof(CSSOM_CSSRuleList));
  if (cssRules == NULL) {
    CSSOM_Deque_CSSRule_free(data);
    return NULL;
  }

  cssRules->data = data;

  return cssRules;
}



void CSSOM_CSSRuleList__acquire(CSSOM_CSSRuleList *cssRules) {
  ++cssRules->handles;
}



void CSSOM_CSSRuleList__release(CSSOM_CSSRuleList *cssRules) {
  CSSOM_DequeIter_CSSRule it;

  assert(cssRules->handles > 0);
  --cssRules->handles;
  if (cssRules->handles > 0) return;

  for (it = CSSOM_Deque_CSSRule_begin(cssRules->data);
    it != CSSOM_Deque_CSSRule_end(cssRules->data);
    it = CSSOM_DequeIter_CSSRule_next(it))
  {
    CSSOM_CSSRule__release(*it);
  }

  free(cssRules);
}



CSSOM_CSSRule* CSSOM_CSSRuleList__append(CSSOM_CSSRuleList *cssRules,
  CSSOM_CSSRule *cssRule)
{
  CSSOM_DequeIter_CSSRule it;

  it = CSSOM_Deque_CSSRule_append(cssRules->data, cssRule);
  if (it == CSSOM_Deque_CSSRule_end(cssRules->data)) return NULL;

  return *it;
}



size_t CSSOM_CSSRuleList_size(const CSSOM_CSSRuleList *cssRules) {
  return CSSOM_Deque_CSSRule_size(cssRules->data);
}



CSSOM_CSSRule* CSSOM_CSSRuleList_at(const CSSOM_CSSRuleList *cssRules,
  size_t index)
{
  return *CSSOM_Deque_CSSRule_at(cssRules->data, index);
}
