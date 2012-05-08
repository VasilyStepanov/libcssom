#include "NodeImpl.hpp"

#include "NodeListImpl.hpp"

#include <sstream>

#include <assert.h>

namespace {



std::string empty;



} // unnamed

namespace test {



NodeImpl::NodeImpl(const std::string &name, const std::string &content,
  const std::map<std::string, std::string> &attributes,
  test::NodeListImpl *children) :
  _handles(1),
  _name(name),
  _content(content),
  _attributes(attributes),
  _children(children),
  _previousSibling(NULL),
  _nextSibling(NULL)
{}



void NodeImpl::acquire() {
  if (this == NULL) return;

  ++_handles;
}



void NodeImpl::release() {
  if (this == NULL) return;

  assert(_handles > 0);
  --_handles;
  if (_handles > 0) return;

  delete _children;
}



std::string NodeImpl::str() const {
  std::ostringstream oss;

  if (_name == "#text") {
    oss << _content;    
  } else {
    oss << "<" << _name;
    for (
      std::map<std::string, std::string>::const_iterator it =
        _attributes.begin();
      it != _attributes.end();
      ++it)
    {
      oss << " " << it->first << "=\"" << it->second << "\"";
    }
    oss << ">";

    for (size_t i = 0; i < _children->size(); ++i)
      oss << (*_children)[i]->str();

    oss << "</" << _name << ">";
  }

  return oss.str();
}



const std::string& NodeImpl::name() const {
  return _name;
}



const std::string& NodeImpl::content() const {
  return _content;
}



const std::string& NodeImpl::getAttribute(const std::string &name) const {
  std::map<std::string, std::string>::const_iterator match =
    _attributes.find(name);

  if (match == _attributes.end()) return empty;

  return match->second;
}



test::NodeListImpl* NodeImpl::children() const {
  return _children;
}



void NodeImpl::setPreviousSibling(test::NodeImpl *sibling) {
  _previousSibling = sibling;
}



test::NodeImpl* NodeImpl::previousSibling() const {
  return _previousSibling;
}



void NodeImpl::setNextSibling(test::NodeImpl *sibling) {
  _nextSibling = sibling;
}



test::NodeImpl* NodeImpl::nextSibling() const {
  return _nextSibling;
}



} // test
