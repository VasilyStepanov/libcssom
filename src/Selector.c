#include "Selector.h"

#include "CSSEmitter.h"
#include "CSSStyleSheet.h"
#include "CSSOM.h"
#include "Deque_void.h"
#include "gcc.h"
#include "memory.h"
#include "utility.h"

#include <cssom/CSSRule.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>



struct _CSSOM_Selector_vtable {
  const char* (*selectorText)(const CSSOM_Selector *selector);
  void (*setSelectorText)(CSSOM_Selector *selector, const char *selectorText);
};



struct _CSSOM_Selector {
  const struct _CSSOM_Selector_vtable *vtable;
  size_t handles;
  const CSSOM *cssom;
  SAC_Parser parser;
  CSSOM_CSSRule *parentRule;
  char *selectorText;
  const SAC_Selector **selectors;
};



static void Selector_swap(CSSOM_Selector *lhs, CSSOM_Selector *rhs) {
  assert(lhs->parentRule == rhs->parentRule);
  SWAPP(lhs->parser, rhs->parser);
  SWAPP(lhs->selectorText, rhs->selectorText);
  SWAPP(lhs->selectors, rhs->selectors);
}



static void Selector_ctor(CSSOM_Selector *selector,
  const struct _CSSOM_Selector_vtable *vtable, const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const SAC_Selector *selectors[])
{
  selector->vtable = vtable;
  selector->handles = 1;
  selector->cssom = cssom;
  selector->parser = NULL;
  selector->parentRule = parentRule;
  selector->selectorText = NULL;
  selector->selectors = selectors;
}



static const char* Selector_selectorText(const CSSOM_Selector *selector) {
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(selector->selectorText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_selector(out, selector) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_Selector*)selector)->selectorText = buf;

  return selector->selectorText;
}



static void Selector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  CSSOM_Selector *newSelector;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(selector->parentRule));
  newSelector = CSSOM__parseSelector(cssom, selector->parentRule,
    selectorText, strlen(selectorText));
  if (newSelector == NULL) return;

  Selector_swap(selector, newSelector);

  CSSOM_Selector_release(newSelector);
}



static const struct _CSSOM_Selector_vtable Selector_vtable = {
  Selector_selectorText,
  Selector_setSelectorText
};



CSSOM_Selector* CSSOM_Selector__alloc(const CSSOM *cssom,
  CSSOM_CSSRule *parentRule, const SAC_Selector *selectors[])
{
  CSSOM_Selector *selector;

  selector = (CSSOM_Selector*)CSSOM_malloc(sizeof(CSSOM_Selector));
  if (selector == NULL) return NULL;
  
  Selector_ctor(selector, &Selector_vtable, cssom, parentRule, selectors);

  return selector;
}



static const char* PageSelector_selectorText(const CSSOM_Selector *selector) {
  FILE *out;
  char *buf;
  size_t bufsize;

  CSSOM_native_free(selector->selectorText);

  buf = NULL;
  out = open_memstream(&buf, &bufsize);
  if (out == NULL) return NULL;

  if (CSSOM_CSSEmitter_pageSelector(out, selector) != 0) {
    fclose(out);
    CSSOM_native_free(buf);
    return NULL;
  }

  if (fclose(out) != 0) {
    CSSOM_native_free(buf);
    return NULL;
  }

  ((CSSOM_Selector*)selector)->selectorText = buf;

  return selector->selectorText;
}



static void PageSelector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  CSSOM_Selector *newSelector;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet(selector->parentRule));
  newSelector = CSSOM__parsePageSelector(cssom, selector->parentRule,
    selectorText, strlen(selectorText));
  if (newSelector == NULL) return;

  Selector_swap(selector, newSelector);

  CSSOM_Selector_release(newSelector);
}



static const struct _CSSOM_Selector_vtable PageSelector_vtable = {
  PageSelector_selectorText,
  PageSelector_setSelectorText
};



CSSOM_Selector* CSSOM_PageSelector__alloc(const CSSOM *cssom,
  CSSOM_CSSPageRule *parentRule, const SAC_Selector *selectors[])
{
  CSSOM_Selector *selector;

  selector = (CSSOM_Selector*)CSSOM_malloc(sizeof(CSSOM_Selector));
  if (selector == NULL) return NULL;
  
  Selector_ctor(selector, &PageSelector_vtable,
    cssom, (CSSOM_CSSRule*)parentRule, selectors);

  return selector;
}



void CSSOM_Selector_acquire(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  ++selector->handles;
  CSSOM_CSSRule_acquire(selector->parentRule);
}



void CSSOM_Selector_release(CSSOM_Selector *selector) {
  if (selector == NULL) return;

  assert(selector->handles > 0);
  --selector->handles;
  if (selector->handles > 0) {
    CSSOM_CSSRule_release(selector->parentRule);
    return;
  }

  CSSOM_native_free(selector->selectorText);
  SAC_DisposeParser(selector->parser);
  CSSOM_free(selector);
}



void CSSOM_Selector__setParentRule(CSSOM_Selector *selector,
  CSSOM_CSSRule *parentRule)
{
  size_t i;

  for (i = 0; i < selector->handles - 1; ++i) {
    CSSOM_CSSRule_release(selector->parentRule);
    CSSOM_CSSRule_acquire(parentRule);
  }

  selector->parentRule = parentRule;
}



CSSOM_CSSRule* CSSOM_Selector_parentRule(const CSSOM_Selector *selector) {
  return selector->parentRule;
}



const char* CSSOM_Selector_selectorText(const CSSOM_Selector *selector) {
  return selector->vtable->selectorText(selector);
}



void CSSOM_Selector_setSelectorText(CSSOM_Selector *selector,
  const char *selectorText)
{
  selector->vtable->setSelectorText(selector, selectorText);
}



const SAC_Selector** CSSOM_Selector__selectors(const CSSOM_Selector *selector) {
  return selector->selectors;
}



void CSSOM_Selector__keepParser(CSSOM_Selector *selector,
  SAC_Parser parser)
{
  assert(selector->parser == NULL);
  selector->parser = parser;
}



static int performed(const CSSOM_DOMAPI *domapi, const SAC_Condition *condition,
  void *node)
{
  switch (condition->conditionType) {
    case SAC_AND_CONDITION:
      if (performed(domapi,
        condition->desc.combinator.firstCondition, node) == 0)
      {
        return 0;
      }
      if (performed(domapi,
        condition->desc.combinator.secondCondition, node) == 0)
      {
        return 0;
      }
      return 1;
    case SAC_OR_CONDITION:
      fprintf(stderr, "Condition OR not implemented.\n");
      return 0;
    case SAC_NEGATIVE_CONDITION:
      fprintf(stderr, "Negative condition not implemented.\n");
      return 0;
    case SAC_POSITIONAL_CONDITION:
      fprintf(stderr, "Positional condition not implemented.\n");
      return 0;
    case SAC_PREFIX_ATTRIBUTE_CONDITION:
      return domapi->Node_attributePrefix(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_SUFFIX_ATTRIBUTE_CONDITION:
      return domapi->Node_attributeSuffix(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
      return domapi->Node_attributeSubstring(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_ATTRIBUTE_CONDITION:
      return domapi->Node_attributeMatch(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_ID_CONDITION:
      return domapi->Node_id(node, condition->desc.attribute.value);
    case SAC_LANG_CONDITION:
      fprintf(stderr, "Lang condition not implemented.\n");
      return 0;
    case SAC_ONE_OF_ATTRIBUTE_CONDITION:
      return domapi->Node_attributeOneOf(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
      return domapi->Node_attributeBeginHyphen(node,
        condition->desc.attribute.name, condition->desc.attribute.value);
    case SAC_CLASS_CONDITION:
      return domapi->Node_class(node, condition->desc.attribute.value);
    case SAC_PSEUDO_CLASS_CONDITION:
      fprintf(stderr, "Pseudo class condition not implemented.\n");
      return 0;
    case SAC_PSEUDO_ELEMENT_CONDITION:
      fprintf(stderr, "Pseudo element condition not implemented.\n");
      return 0;
    case SAC_ONLY_CHILD_CONDITION:
      fprintf(stderr, "Only child condition not implemented.\n");
      return 0;
    case SAC_ONLY_TYPE_CONDITION:
      fprintf(stderr, "Only type condition not implemented.\n");
      return 0;
    case SAC_CONTENT_CONDITION:
      fprintf(stderr, "Content condition not implemented.\n");
      return 0;
  }
  return 0;
}



static int selected(const CSSOM_DOMAPI *domapi, const SAC_Selector *selector,
  void *node);



static int descendant(const CSSOM_DOMAPI *domapi, const SAC_Selector *selector,
  void *node)
{
  void *parent;

  parent = domapi->Node_parent(node);
  if (parent == NULL) return 0;

  if (selected(domapi, selector, parent) != 0) return 1;

  return descendant(domapi, selector, parent);
}



static int child(const CSSOM_DOMAPI *domapi, const SAC_Selector *selector,
  void *node)
{
  void *parent;

  parent = domapi->Node_parent(node);
  if (parent == NULL) return 0;

  if (selected(domapi, selector, parent) != 0) return 1;

  return 0;
}



static int directadjacent(const CSSOM_DOMAPI *domapi,
  const SAC_Selector *selector, void *node)
{
  void *adjacent;

  adjacent = domapi->Node_prev(node);
  if (adjacent == NULL) return 0;

  if (selected(domapi, selector, adjacent) != 0) return 1;

  return 0;
}



static int generaladjacent(const CSSOM_DOMAPI *domapi,
  const SAC_Selector *selector, void *node)
{
  void *adjacent;

  adjacent = domapi->Node_prev(node);
  if (adjacent == NULL) return 0;

  if (selected(domapi, selector, adjacent) != 0) return 1;

  return generaladjacent(domapi, selector, adjacent);
}



static int selected(const CSSOM_DOMAPI *domapi, const SAC_Selector *selector,
  void *node)
{
  switch (selector->selectorType) {
    case SAC_CONDITIONAL_SELECTOR:
      if (selected(domapi,
        selector->desc.conditional.simpleSelector, node) == 0)
      {
        return 0;
      }
      if (performed(domapi,
        selector->desc.conditional.condition, node) == 0)
      {
        return 0;
      }
      return 1;
    case SAC_ANY_NODE_SELECTOR:
      return 1;
    case SAC_ELEMENT_NODE_SELECTOR:
      return domapi->Node_elementMatch(node, selector->desc.element.name);
    case SAC_TEXT_NODE_SELECTOR:
      fprintf(stderr, "Text node selector not implemented.\n");
      return 0;
    case SAC_CDATA_SECTION_NODE_SELECTOR:
      fprintf(stderr, "CDATA section node selector not implemented.\n");
      return 0;
    case SAC_PROCESSING_INSTRUCTION_NODE_SELECTOR:
      fprintf(stderr, "Processing instruction node selector "
        "not implemented.\n");
      return 0;
    case SAC_COMMENT_NODE_SELECTOR:
      fprintf(stderr, "Comment node selector not implemented.\n");
      return 0;
    case SAC_DESCENDANT_SELECTOR:
      if (selected(domapi, selector->desc.descendant.simpleSelector, node) == 0)
        return 0;
      if (descendant(domapi,
        selector->desc.descendant.descendantSelector, node) == 0)
      {
        return 0;
      }
      return 1;
    case SAC_CHILD_SELECTOR:
      if (selected(domapi, selector->desc.descendant.simpleSelector, node) == 0)
        return 0;
      if (child(domapi,
        selector->desc.descendant.descendantSelector, node) == 0)
      {
        return 0;
      }
      return 1;
    case SAC_DIRECT_ADJACENT_SELECTOR:
      if (selected(domapi, selector->desc.sibling.secondSelector, node) == 0)
        return 0;
      if (directadjacent(domapi,
        selector->desc.sibling.firstSelector, node) == 0)
      {
        return 0;
      }
      return 1;
    case SAC_GENERAL_ADJACENT_SELECTOR:
      if (selected(domapi, selector->desc.sibling.secondSelector, node) == 0)
        return 0;
      if (generaladjacent(domapi,
        selector->desc.sibling.firstSelector, node) == 0)
      {
        return 0;
      }
      return 1;
  }
  return 0;
}



static void Selector_walk(const CSSOM_Selector *selector,
  const CSSOM_DOMAPI *domapi, void *node, void *selection)
{
  const SAC_Selector **it;
  void *child;

  for (it = selector->selectors; *it != NULL; ++it) {
    if (selected(domapi, *it, node) != 0) {
      domapi->Selection_append(selection, node);
      break;
    }
  }

  for (
    child = domapi->Node_children(node);
    child != NULL;
    child = domapi->Node_next(child))
  {
    Selector_walk(selector, domapi, child, selection);
  }
}



void CSSOM_Selector_select(CSSOM_Selector *selector, void *root,
  void *selection)
{
  Selector_walk(selector, CSSOM_getDOMAPI(selector->cssom), root, selection);
}



static void selectorSpecificity(const SAC_Selector *selector,
  unsigned long *a, unsigned long *b, unsigned long *c);



static void conditionSpecificity(const SAC_Condition *condition,
  unsigned long *a, unsigned long *b, unsigned long *c)
{
  switch (condition->conditionType) {
    case SAC_AND_CONDITION:
    case SAC_OR_CONDITION:
      conditionSpecificity(condition->desc.combinator.firstCondition, a, b, c);
      conditionSpecificity(condition->desc.combinator.secondCondition, a, b, c);
      break;
    case SAC_NEGATIVE_CONDITION:
      selectorSpecificity(condition->desc.selector, a, b, c);
      break;
    case SAC_POSITIONAL_CONDITION:
      break;
    case SAC_ID_CONDITION:
      ++*a;
      break;
    case SAC_PREFIX_ATTRIBUTE_CONDITION:
    case SAC_SUFFIX_ATTRIBUTE_CONDITION:
    case SAC_SUBSTRING_ATTRIBUTE_CONDITION:
    case SAC_ATTRIBUTE_CONDITION:
    case SAC_LANG_CONDITION:
    case SAC_ONE_OF_ATTRIBUTE_CONDITION:
    case SAC_BEGIN_HYPHEN_ATTRIBUTE_CONDITION:
    case SAC_CLASS_CONDITION:
    case SAC_PSEUDO_CLASS_CONDITION:
      ++*b;
      break;
    case SAC_PSEUDO_ELEMENT_CONDITION:
      ++*c;
      break;
    case SAC_ONLY_CHILD_CONDITION:
      break;
    case SAC_ONLY_TYPE_CONDITION:
      break;
    case SAC_CONTENT_CONDITION:
      break;
  }
}



static void selectorSpecificity(const SAC_Selector *selector,
  unsigned long *a, unsigned long *b, unsigned long *c)
{
  switch (selector->selectorType) {
    case SAC_CONDITIONAL_SELECTOR:
      selectorSpecificity(selector->desc.conditional.simpleSelector, a, b, c);
      conditionSpecificity(selector->desc.conditional.condition, a, b, c);
      break;
    case SAC_ANY_NODE_SELECTOR:
      break;
    case SAC_ELEMENT_NODE_SELECTOR:
      ++*c;
      break;
    case SAC_TEXT_NODE_SELECTOR:
      break;
    case SAC_CDATA_SECTION_NODE_SELECTOR:
      break;
    case SAC_PROCESSING_INSTRUCTION_NODE_SELECTOR:
      break;
    case SAC_COMMENT_NODE_SELECTOR:
      break;
    case SAC_DESCENDANT_SELECTOR:
    case SAC_CHILD_SELECTOR:
      selectorSpecificity(selector->desc.descendant.simpleSelector, a, b, c);
      selectorSpecificity(selector->desc.descendant.descendantSelector,
        a, b, c);
      break;
    case SAC_DIRECT_ADJACENT_SELECTOR:
    case SAC_GENERAL_ADJACENT_SELECTOR:
      selectorSpecificity(selector->desc.sibling.secondSelector, a, b, c);
      selectorSpecificity(selector->desc.sibling.firstSelector, a, b, c);
      break;
  }
}



unsigned long CSSOM_Selector_specificity(const CSSOM_Selector * selector)
{
  unsigned long a;
  unsigned long b;
  unsigned long c;
  const SAC_Selector **it;

  a = 0;
  b = 0;
  c = 0;
  for (it = selector->selectors; *it != NULL; ++it)
    selectorSpecificity(*it, &a, &b, &c);

  return (a << 0x10) + (b << 0x8) + (c);
}
