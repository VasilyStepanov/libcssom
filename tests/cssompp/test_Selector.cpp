#include "test_Selector.hpp"

#include "Errors.hpp"
#include "Node.hpp"
#include "NodeImpl.hpp"
#include "NodeList.hpp"
#include "NodeListImpl.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/Selector.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <assert.h>
#include <stdio.h>

namespace {



CSSOM_NodeType Node_type(test::Node::Impl *node) {
  if (node->name() == "#text") return CSSOM_TEXT_NODE;
  return CSSOM_ELEMENT_NODE;
}



const char* Node_name(test::Node::Impl *node) {
  return node->name().c_str();
}



test::Node::Impl* Node_children(test::Node::Impl *node) {
  if (node->children()->empty()) return NULL;
  return (*node->children())[0];
}



test::Node::Impl* Node_next(test::Node::Impl *node) {
  if (node->nextSibling() == NULL) return NULL;
  return node->nextSibling();
}



void Selection_append(std::deque<test::Node> *selection,
  test::Node::Impl *node)
{
  selection->push_back(test::Node(node));
}



std::string html(const std::deque<test::Node> &nodes) {
  std::ostringstream oss;

  for (
    std::deque<test::Node>::const_iterator it = nodes.begin();
    it != nodes.end();
    ++it)
  {
    oss << it->str();
  }

  return oss.str();
}



void select(const test::Node &root, cssom::Selector &selector,
  std::deque<test::Node> &selection)
{
  std::deque<test::Node> ret;

  selector.select((void*)root.impl(), (void*)&ret);

  selection.swap(ret);
}



void selectorText() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::Selector selector = cssom.parseSelector("p");



  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());
}



cssom::CSSOM setup() {
  CSSOM_DOMAPI domapi = {
    (CSSOM_NodeType(*)(void*))Node_type,
    (const char*(*)(void*))Node_name,
    (void*(*)(void*))Node_children,
    (void*(*)(void*))Node_next,
    (void(*)(void*, void*))Selection_append,
  };

  cssom::CSSOM cssom;
  cssom.setDOMAPI(&domapi);

  return cssom;
}



void universalSelector() {
  cssom::CSSOM cssom = setup();
  cssom::Selector selector = cssom.parseSelector("*");

  test::Node root = test::Node::parse(
"<div>\n"
  "<p>Paragraph.</p>\n"
"</div>\n"
  );

  std::deque<test::Node> selection;
  select(root, selector, selection);

  assertEquals(std::string(
"<html><body><div>\n"
"<p>Paragraph.</p>\n"
"</div></body></html>"
"<body><div>\n"
"<p>Paragraph.</p>\n"
"</div></body>"
"<div>\n"
"<p>Paragraph.</p>\n"
"</div>\n"
"<p>Paragraph.</p>"
"Paragraph.\n"
  ), html(selection));
}



void typeSelector() {
  cssom::CSSOM cssom = setup();
  cssom::Selector selector = cssom.parseSelector("h1");

  test::Node root = test::Node::parse(
"<div>\n"
  "<h1>Title</h1>\n"
  "<p>Paragraph.</p>\n"
"</div>\n"
  );

  std::deque<test::Node> selection;
  select(root, selector, selection);

  assertEquals(std::string(
"<h1>Title</h1>"
  ), html(selection));
}



} // unnamed

namespace test {



void selector() {
  selectorText();
  universalSelector();
  typeSelector();
}



} // test
