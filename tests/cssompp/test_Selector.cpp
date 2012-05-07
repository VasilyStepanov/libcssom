#include "test_Selector.hpp"

#include "Errors.hpp"
#include "Node.hpp"
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



template <typename T>
void* wrap(const T &t) {
  return *(void**)&t;
}



template <typename T>
T* unwrap(void *p) {
  T *t = (T*)&p;
  return t;
}



static const char* Node_name(void *node) {
  return unwrap<test::Node>(node)->name().c_str();
}



static void Selection_appendNode(std::deque<test::Node> *selection,
  void *node)
{
  selection->push_back(*unwrap<test::Node>(node));
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

  selector.select(wrap(root), (void*)&ret);

  selection.swap(ret);
}



void selectorText() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::Selector selector = cssom.parseSelector("p");



  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());
}



void selectElements() {
  CSSOM_DOMAPI domapi = {
    Node_name,
    (void(*)(void*, void*))Selection_appendNode,
  };

  cssom::CSSOM cssom;
  cssom.setDOMAPI(&domapi);
  cssom::Selector selector = cssom.parseSelector("span");

  test::Node root = test::Node::parse(
"<div>\n"
  "<p>Skip.</p>\n"
  "<span>Paragraph <span>with</span> spans.</span>\n"
  "<p>Skip.</p>\n"
"</div>\n"
  );

  std::deque<test::Node> selection;
  select(root, selector, selection);

  assertEquals(std::string(
"<span>Paragraph <span>with</span> spans.</span>"
"<span>with</span>"
  ), html(selection));
}



} // unnamed

namespace test {



void selector() {
  selectorText();
  selectElements();
}



} // test
