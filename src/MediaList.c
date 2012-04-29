#include "MediaList.h"

#include "MediaQuery.h"
#include "CSSEmitter.h"
#include "CSSOM.h"
#include "CSSRule.h"
#include "CSSStyleSheet.h"
#include "Deque_MediaQuery.h"
#include "memory.h"
#include "gcc.h"
#include "utility.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>



struct _CSSOM_MediaList {
  size_t handles;
  SAC_Parser parser;
  CSSOM_CSSMediaRule *ownerRule;
  char *mediaText;
  const SAC_MediaQuery **query;
  CSSOM_Deque_MediaQuery *data;
};



static void MediaDeque_free(CSSOM_Deque_MediaQuery *deque) {
  CSSOM_DequeIter_MediaQuery it;

  for (
    it = CSSOM_Deque_MediaQuery_begin(deque);
    it != CSSOM_Deque_MediaQuery_end(deque);
    it = CSSOM_DequeIter_MediaQuery_next(it))
  {
    CSSOM_MediaQuery_release(*it);
  }

  CSSOM_Deque_MediaQuery_free(deque);
}



static void MediaList_swap(CSSOM_MediaList *lhs, CSSOM_MediaList *rhs) {
  SWAP(lhs->parser, rhs->parser);
  SWAP(lhs->ownerRule, rhs->ownerRule);
  SWAP(lhs->mediaText, rhs->mediaText);
  SWAP(lhs->query, rhs->query);
  SWAP(lhs->data, rhs->data);
}



/**
 * TODO: Optimize me.
 */
static CSSOM_DequeIter_MediaQuery MediaDeque_find(
  CSSOM_Deque_MediaQuery *deque, const CSSOM_MediaQuery *query)
{
  const char *match;
  CSSOM_DequeIter_MediaQuery it;

  match = CSSOM_MediaQuery_mediaText(query);
  if (match == NULL) return CSSOM_Deque_MediaQuery_end(deque);

  for (
    it = CSSOM_Deque_MediaQuery_begin(deque);
    it != CSSOM_Deque_MediaQuery_end(deque);
    it = CSSOM_DequeIter_MediaQuery_next(it))
  {
    if (strcmp(CSSOM_MediaQuery_mediaText(*it), match) == 0) return it;
  }

  return CSSOM_Deque_MediaQuery_end(deque);
}



CSSOM_MediaList* CSSOM_MediaList__alloc(CSSOM_CSSMediaRule *ownerRule,
  const SAC_MediaQuery **query)
{
  CSSOM_MediaList *media;
  CSSOM_Deque_MediaQuery *data;
  const SAC_MediaQuery **it;
  size_t size;

  for (it = query, size = 0; *it != NULL; ++it) ++size;

  data = CSSOM_Deque_MediaQuery_alloc_ex(0, size);
  if (data == NULL) return NULL;

  media = (CSSOM_MediaList*)CSSOM_malloc(sizeof(CSSOM_MediaList));
  if (media == NULL) {
    CSSOM_Deque_MediaQuery_free(data);
    return NULL;
  }

  for (it = query; *it != NULL; ++it) {
    CSSOM_MediaQuery *query;

    query = CSSOM_MediaQuery__alloc(media, *it);
    if (query == NULL) {
      CSSOM_MediaList_release(media);
      MediaDeque_free(data);
      return NULL;
    }

    if (MediaDeque_find(data, query) != CSSOM_Deque_MediaQuery_end(data)) {
      CSSOM_MediaQuery_release(query);
      continue;
    }

    if (CSSOM_Deque_MediaQuery_append(data, query) ==
      CSSOM_Deque_MediaQuery_end(data))
    {
      CSSOM_MediaQuery_release(query);
      CSSOM_MediaList_release(media);
      MediaDeque_free(data);
      return NULL;
    }

  }

  media->handles = 1;
  media->parser = NULL;
  media->ownerRule = ownerRule;
  media->mediaText = NULL;
  media->query = query;
  media->data = data;

  return media;
}



void CSSOM_MediaList_acquire(CSSOM_MediaList *media) {
  if (media == NULL) return;

  ++media->handles;
  CSSOM_CSSRule_acquire((CSSOM_CSSRule*)media->ownerRule);
}



void CSSOM_MediaList_release(CSSOM_MediaList *media) {
  if (media == NULL) return;

  assert(media->handles > 0);
  --media->handles;
  if (media->handles > 0) {
    CSSOM_CSSRule_release((CSSOM_CSSRule*)media->ownerRule);
    return;
  }

  MediaDeque_free(media->data);
  CSSOM_native_free(media->mediaText);
  SAC_DisposeParser(media->parser);
  CSSOM_free(media);
}



const SAC_MediaQuery** CSSOM_MediaList__query(const CSSOM_MediaList *media) {
  return media->query;
}



void CSSOM_MediaList_setMediaText(CSSOM_MediaList *media,
  const char *mediaText)
{
  CSSOM_MediaList *newMedia;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet((CSSOM_CSSRule*)media->ownerRule));
  newMedia = CSSOM__parseMedia(cssom, media->ownerRule,
    mediaText, strlen(mediaText));
  if (newMedia == NULL) return;

  MediaList_swap(media, newMedia);

  CSSOM_MediaList_release(newMedia);
}



const char* CSSOM_MediaList_mediaText(const CSSOM_MediaList *media) {
  if (media->mediaText == NULL) {
    FILE *out;
    char *buf;
    size_t bufsize;

    buf = NULL;
    out = open_memstream(&buf, &bufsize);
    if (out == NULL) return NULL;

    if (CSSOM_CSSEmitter_media(out, media) != 0) {
      fclose(out);
      CSSOM_free(buf);
      return NULL;
    }

    if (fclose(out) != 0) {
      CSSOM_free(buf);
      return NULL;
    }

    ((CSSOM_MediaList*)media)->mediaText = buf;
  }
  return media->mediaText;
}



unsigned long CSSOM_MediaList_length(const CSSOM_MediaList *media) {
  return CSSOM_Deque_MediaQuery_size(media->data);
}



const char * CSSOM_MediaList_item(const CSSOM_MediaList *media,
  unsigned long index)
{
  CSSOM_MediaQuery *query;

  if (index >= CSSOM_Deque_MediaQuery_size(media->data)) return NULL;

  query = *CSSOM_Deque_MediaQuery_at(media->data, index);

  return CSSOM_MediaQuery_mediaText(query);
}



CSSOM_MediaQuery* CSSOM_MediaList__at(const CSSOM_MediaList *media,
  unsigned long index)
{
  return *CSSOM_Deque_MediaQuery_at(media->data, index);
}



void CSSOM_MediaList__keepParser(CSSOM_MediaList *media,
  SAC_Parser parser)
{
  media->parser = parser;
}



void CSSOM_MediaList_appendMedium(CSSOM_MediaList *media,
  const char *medium)
{
  CSSOM_MediaQuery *query;
  const CSSOM *cssom;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet((CSSOM_CSSRule*)media->ownerRule));
  query = CSSOM__parseMediaQuery(cssom, media, medium, strlen(medium));
  if (query == NULL) return;

  if (MediaDeque_find(media->data, query) !=
    CSSOM_Deque_MediaQuery_end(media->data))
  {
    CSSOM_MediaQuery_release(query);
    return;
  }

  if (CSSOM_Deque_MediaQuery_append(media->data, query) ==
    CSSOM_Deque_MediaQuery_end(media->data))
  {
    CSSOM_MediaQuery_release(query);
    return;
  }
}



void CSSOM_MediaList_deleteMedium(CSSOM_MediaList *media,
  const char * medium)
{
  CSSOM_MediaQuery *query;
  const CSSOM *cssom;
  CSSOM_DequeIter_MediaQuery match;

  cssom = CSSOM_CSSStyleSheet__cssom(
    CSSOM_CSSRule_parentStyleSheet((CSSOM_CSSRule*)media->ownerRule));
  query = CSSOM__parseMediaQuery(cssom, media, medium, strlen(medium));
  if (query == NULL) return;

  match = MediaDeque_find(media->data, query);
  if (match == CSSOM_Deque_MediaQuery_end(media->data)) {
    CSSOM_MediaQuery_release(query);
    return;
  }

  CSSOM_Deque_MediaQuery_erase(media->data, match);
}
