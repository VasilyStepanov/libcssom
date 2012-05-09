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



const char* Node_attribute(test::Node::Impl *node, const char *name) {
  if (!node->hasAttribute(name)) return NULL;
  return node->getAttribute(name).c_str();
}



const char* Node_class(test::Node::Impl *node) {
  if (!node->hasAttribute("class")) return NULL;
  return node->getAttribute("class").c_str();
}



const char* Node_id(test::Node::Impl *node) {
  if (!node->hasAttribute("id")) return NULL;
  return node->getAttribute("id").c_str();
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
    (const char*(*)(void*, const char*))Node_attribute,
    (const char*(*)(void*))Node_class,
    (const char*(*)(void*))Node_id,
    (void*(*)(void*))Node_children,
    (void*(*)(void*))Node_next,
    (void(*)(void*, void*))Selection_append,
  };

  cssom::CSSOM cssom;
  cssom.setDOMAPI(&domapi);

  return cssom;
}



void typeSelector() {
  cssom::CSSOM cssom = setup();
  std::deque<test::Node> selection;
  cssom::Selector selector;

  /**
   * 6.1. Type selector
   */

  test::Node root = test::Node::parse(
"<div>"
  "<h1>Title</h1>"
  "<p>Paragraph.</p>"
"</div>"
  );



  selector = cssom.parseSelector("h1");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1>Title</h1>"
  ), html(selection));
}



void universalSelector() {
  cssom::CSSOM cssom = setup();
  std::deque<test::Node> selection;
  cssom::Selector selector;

  /**
   * 6.2. Universal selector
   */

  test::Node root = test::Node::parse(
"<div>"
  "<p>Paragraph.</p>"
"</div>"
  );



  selector = cssom.parseSelector("*");
  select(root, selector, selection);
  assertEquals(std::string(

"<div>"
"<p>Paragraph.</p>"
"</div>"

"<p>Paragraph.</p>"

"Paragraph."

  ), html(selection));
}



void attributeSelector() {
  cssom::CSSOM cssom = setup();
  std::deque<test::Node> selection;
  cssom::Selector selector;

  /**
   * 6.3.1. Attribute presence and value selectors
   */

  test::Node root = test::Node::parse(
"<div>"

  "<h1 title=\"chapter1\">Chapter 1</h1>"
  "<h1>Chapter 2</h1>"

  "<span>span</span>"
  "<span class=\"generic\">generic span</span>"
  "<span class=\"example\">example span</span>"

  "<span hello=\"Cleveland\">Hello Cleveland</span>"
  "<span goodbye=\"Columbus\">Goodbye Columbus</span>"
  "<span goodbye=\"Columbus\" hello=\"Cleveland\">"
    "Hello Cleveland, goodbye Columbus</span>"

  "<a rel=\"copyright copyleft copyeditor\">copying</a>"

  "<a hreflang=\"fr\">french</a>"

  "<a hreflang=\"en\">english</a>"
  "<a hreflang=\"en-US\">us english</a>"
  "<a hreflang=\"en-scouse\">scouse english</a>"
  "<a hreflang=\"envalid\">invalid</a>"

  "<object type=\"image/gif\"></object>"

  "<a href=\"http://example.com/foo.html\">foo</a>"

  "<p title=\"sayhelloworld\">Hello world</p>"

"</div>"
  );



  selector = cssom.parseSelector("h1[title]");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 title=\"chapter1\">Chapter 1</h1>"
  ), html(selection));



  selector = cssom.parseSelector("span[class=\"example\"]");
  select(root, selector, selection);
  assertEquals(std::string(
"<span class=\"example\">example span</span>"
  ), html(selection));



  selector = cssom.parseSelector(
"span[hello=\"Cleveland\"][goodbye=\"Columbus\"]"
  );
  select(root, selector, selection);
  assertEquals(std::string(
"<span goodbye=\"Columbus\" hello=\"Cleveland\">"
  "Hello Cleveland, goodbye Columbus</span>"
  ), html(selection));



  selector = cssom.parseSelector("a[rel~=\"copyright\"]");
  select(root, selector, selection);
  assertEquals(std::string(
"<a rel=\"copyright copyleft copyeditor\">copying</a>"
  ), html(selection));



  selector = cssom.parseSelector("a[hreflang=fr]");
  select(root, selector, selection);
  assertEquals(std::string(
"<a hreflang=\"fr\">french</a>"
  ), html(selection));



  selector = cssom.parseSelector("a[hreflang|=en]");
  select(root, selector, selection);
  assertEquals(std::string(
"<a hreflang=\"en\">english</a>"
"<a hreflang=\"en-US\">us english</a>"
"<a hreflang=\"en-scouse\">scouse english</a>"
  ), html(selection));



  selector = cssom.parseSelector("object[type^=\"image/\"]");
  select(root, selector, selection);
  assertEquals(std::string(
"<object type=\"image/gif\"></object>"
  ), html(selection));



  selector = cssom.parseSelector("a[href$=\".html\"]");
  select(root, selector, selection);
  assertEquals(std::string(
"<a href=\"http://example.com/foo.html\">foo</a>"
  ), html(selection));



  selector = cssom.parseSelector("p[title*=\"hello\"]");
  select(root, selector, selection);
  assertEquals(std::string(
"<p title=\"sayhelloworld\">Hello world</p>"
  ), html(selection));
}



void classSelector() {
  cssom::CSSOM cssom = setup();
  std::deque<test::Node> selection;
  cssom::Selector selector;

  /**
   * 6.4. Class selectors
   */

  test::Node root = test::Node::parse(
"<div>"

"<h1>Not green</h1>"
"<h1 class=\"pastoral\">Very green</h1>"

"<p class=\"pastoral blue\">Skip</p>"
"<p class=\"pastoral blue aqua marine\">Marine</p>"

"</div>"
  );



  selector = cssom.parseSelector("*.pastoral");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 class=\"pastoral\">Very green</h1>"
"<p class=\"pastoral blue\">Skip</p>"
"<p class=\"pastoral blue aqua marine\">Marine</p>"
  ), html(selection));



  selector = cssom.parseSelector(".pastoral");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 class=\"pastoral\">Very green</h1>"
"<p class=\"pastoral blue\">Skip</p>"
"<p class=\"pastoral blue aqua marine\">Marine</p>"
  ), html(selection));



  selector = cssom.parseSelector("h1.pastoral");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 class=\"pastoral\">Very green</h1>"
  ), html(selection));



  selector = cssom.parseSelector("p.pastoral.marine");
  select(root, selector, selection);
  assertEquals(std::string(
"<p class=\"pastoral blue aqua marine\">Marine</p>"
  ), html(selection));
}



void idSelector() {
  cssom::CSSOM cssom = setup();
  std::deque<test::Node> selection;
  cssom::Selector selector;

  /**
   * 6.5. ID selectors
   */

  test::Node root = test::Node::parse(
"<div>"

"<h1 id=\"chapter1\">Chapter 1</h1>"

"<p id=\"chapter1\">Paragraph 1</p>"

"<p id=\"z98y\">Paragraph 2</p>"

"</div>"
  );



  selector = cssom.parseSelector("h1#chapter1");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 id=\"chapter1\">Chapter 1</h1>"
  ), html(selection));



  selector = cssom.parseSelector("#chapter1");
  select(root, selector, selection);
  assertEquals(std::string(
"<h1 id=\"chapter1\">Chapter 1</h1>"
"<p id=\"chapter1\">Paragraph 1</p>"
  ), html(selection));



  selector = cssom.parseSelector("*#z98y");
  select(root, selector, selection);
  assertEquals(std::string(
"<p id=\"z98y\">Paragraph 2</p>"
  ), html(selection));
}



} // unnamed

namespace test {



void selector() {
  selectorText();

  typeSelector();
  universalSelector();
  attributeSelector();
  classSelector();
  idSelector();
}



} // test
