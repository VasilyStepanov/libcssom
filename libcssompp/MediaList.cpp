#include <cssompp/MediaList.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSMediaRule.idl'
 */



#include <cssom/MediaList.h>

#include "checks.hpp"

#include <utility>

namespace cssom {



MediaList::MediaList() :
  _impl(NULL)
{}



MediaList::MediaList(CSSOM_MediaList * impl) :
  _impl(impl)
{
  CSSOM_MediaList_acquire(_impl);
}



MediaList::MediaList(const cssom::MediaList &copy) :
  _impl(copy._impl)
{
  CSSOM_MediaList_acquire(_impl);
}



MediaList::~MediaList() {
  CSSOM_MediaList_release(_impl);
}



cssom::MediaList& MediaList::operator=(
  const cssom::MediaList &rhs)
{
  if (&rhs == this) return *this;

  cssom::MediaList(rhs).swap(*this);

  return *this;
}



bool MediaList::operator==(
  const cssom::MediaList &rhs) const
{
  return _impl == rhs._impl;
}



bool MediaList::isNull() const {
  return _impl == NULL;
}



void MediaList::swap(cssom::MediaList &rhs) {
  std::swap(_impl, rhs._impl);
}



MediaList::operator const char *() {
  return CSSOM_MediaList_mediaText(_impl);
}



const char * MediaList::operator[](unsigned long index) const {
  return CSSOM_MediaList_item(_impl, index);
}



const char * MediaList::mediaText() const {
  return CSSOM_MediaList_mediaText(_impl);
}



void MediaList::setMediaText(const char * mediaText) {
  CSSOM_MediaList_setMediaText(_impl, mediaText);
}



unsigned long MediaList::length() const {
  return CSSOM_MediaList_length(_impl);
}



const char * MediaList::item(unsigned long index) const {
  return CSSOM_MediaList_item(_impl, index);
}



void MediaList::appendMedium(const char * medium) {
  return CSSOM_MediaList_appendMedium(_impl, medium);
}



void MediaList::deleteMedium(const char * medium) {
  return CSSOM_MediaList_deleteMedium(_impl, medium);
}



} // cssom
