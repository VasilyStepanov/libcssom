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



inline void* wrap(test::Node::Impl *impl) {
  return reinterpret_cast<void*>(impl);
}



inline test::Node::Impl* unwrap(void *p) {
  return reinterpret_cast<test::Node::Impl*>(p);
}



const char* Node_name(void *node) {
  return unwrap(node)->name().c_str();
}



void* Node_children(void *node) {
  if (unwrap(node)->children()->empty()) return NULL;
  return wrap((*unwrap(node)->children())[0]);
}



void* Node_next(void *node) {
  if (unwrap(node)->nextSibling() == NULL) return NULL;
  return wrap(unwrap(node)->nextSibling());
}



void Selection_append(std::deque<test::Node> *selection,
  void *node)
{
  selection->push_back(test::Node(unwrap(node)));
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

  selector.select(wrap(root.impl()), (void*)&ret);

  selection.swap(ret);
}



void selectorText() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::Selector selector = cssom.parseSelector("p");



  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());
}



void universalSelector() {
  CSSOM_DOMAPI domapi = {
    Node_name,
    Node_children,
    Node_next,
    (void(*)(void*, void*))Selection_append,
  };

  cssom::CSSOM cssom;
  cssom.setDOMAPI(&domapi);
  cssom::Selector selector = cssom.parseSelector("span");

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



} // unnamed

namespace test {



void selector() {
  selectorText();
  universalSelector();
}



} // test
