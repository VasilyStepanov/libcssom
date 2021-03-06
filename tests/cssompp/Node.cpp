#include "Node.hpp"

#include "NodeImpl.hpp"
#include "NodeList.hpp"
#include "NodeListImpl.hpp"

#include <utility>
#include <sstream>
#include <stdexcept>
#include <deque>

#include <libxml/HTMLparser.h>

namespace {



std::string nodeName(xmlNode *node) {
  if (node->type == XML_CDATA_SECTION_NODE) return "#cimpl-section";
  if (node->type == XML_ELEMENT_NODE) return (const char*)node->name;
  if (node->type == XML_TEXT_NODE) return "#text";
  if (node->name == NULL) {
    std::ostringstream oss;
    oss << "nodeName(): Node name is null for type: " << node->type;
    throw std::runtime_error(oss.str());
  }
  return (const char*)node->name;
}



test::NodeImpl* create(xmlNode *node, std::deque<test::NodeImpl*> *children) {
  std::string name = nodeName(node);
  std::string content;
  if (node->content != NULL) content = (const char*)node->content;
  std::string ns;
  if (node->ns != NULL && node->ns->prefix != NULL)
    ns = (const char*)node->ns->prefix;

  std::map<std::string, std::string> attributes;

  switch (node->type) {
    case XML_ELEMENT_NODE:
      {
        for (
          xmlAttr *attr = node->properties;
          attr != NULL;
          attr = attr->next)
        {
          if (attr->name == NULL)
            throw std::runtime_error("create(): Attr name is NULL.");

          std::string content;
          if (attr->children != NULL && attr->children->content != NULL)
            content = (const char*)attr->children->content;

          attributes.insert(std::map<std::string, std::string>::value_type(
            (const char*)attr->name, content));
        }
      }
      break;
    case XML_TEXT_NODE:
    case XML_CDATA_SECTION_NODE:
    case XML_COMMENT_NODE:
      break;
    case XML_ATTRIBUTE_NODE:
    case XML_ENTITY_REF_NODE:
    case XML_ENTITY_NODE:
    case XML_PI_NODE:
    case XML_DOCUMENT_NODE:
    case XML_DOCUMENT_TYPE_NODE:
    case XML_DOCUMENT_FRAG_NODE:
    case XML_NOTATION_NODE:
    case XML_HTML_DOCUMENT_NODE:
    case XML_DTD_NODE:
    case XML_ELEMENT_DECL:
    case XML_ATTRIBUTE_DECL:
    case XML_ENTITY_DECL:
    case XML_NAMESPACE_DECL:
    case XML_XINCLUDE_START:
    case XML_XINCLUDE_END:
    case XML_DOCB_DOCUMENT_NODE:
      {
        std::ostringstream oss;
        oss << "create(): Can not create node with type: " << node->type;
        throw std::runtime_error(oss.str());
      }
      break;
  }

  return new test::NodeImpl(ns, name, content, attributes,
    new test::NodeListImpl(children));
}



test::NodeImpl* walk(xmlNode *node) {
  std::deque<test::NodeImpl*> *children = new std::deque<test::NodeImpl*>();

  for (xmlNode *it = node->children; it != NULL; it = it->next)
    children->push_back(walk(it));

  return create(node, children);
}



}

namespace test {



test::Node Node::parse(const std::string &html) {
  xmlParserCtxtPtr parser = xmlCreatePushParserCtxt(
    NULL, NULL, NULL, 0, NULL);
  xmlCtxtUseOptions(parser, XML_PARSE_RECOVER | XML_PARSE_NOERROR |
    XML_PARSE_NOBLANKS | XML_PARSE_NOWARNING | XML_PARSE_NONET);
  xmlParseChunk(parser, html.c_str(), html.length(), 1);

  test::NodeImpl *nodeData = walk(xmlDocGetRootElement(parser->myDoc));
  test::Node wrap(nodeData);
  nodeData->release();

  htmlFreeParserCtxt(parser);

  return wrap;
}



Node::Node() :
  _impl(NULL)
{}



Node::Node(test::NodeImpl *impl) :
  _impl(impl)
{
  _impl->acquire();
}



Node::Node(const test::Node &copy) :
  _impl(copy._impl)
{
  _impl->acquire();
}



Node::~Node() {
  _impl->release();
}



test::Node& Node::operator=(const test::Node &rhs) {
  test::Node(rhs).swap(*this);
  return *this;
}



bool Node::operator==(const test::Node &rhs) const {
  return _impl == rhs._impl;
}


std::string Node::str() const {
  return _impl->str();
}



void Node::swap(test::Node &rhs) {
  std::swap(_impl, rhs._impl);
}



test::NodeImpl* Node::impl() const {
  return _impl;
}



const std::string& Node::name() const {
  return _impl->name();
}



bool Node::hasAttribute(const std::string &name) const {
  return _impl->hasAttribute(name);
}



const std::string& Node::getAttribute(const std::string &name) const {
  return _impl->getAttribute(name);
}



test::Node Node::parent() const {
  return test::Node(_impl->parent());
}



test::NodeList Node::children() const {
  return test::NodeList(_impl->children());
}



test::Node Node::previousSibling() const {
  return test::Node(_impl->previousSibling());
}



test::Node Node::nextSibling() const {
  return test::Node(_impl->nextSibling());
}



} // test
