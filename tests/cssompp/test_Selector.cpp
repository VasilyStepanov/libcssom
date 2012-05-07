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

namespace {



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



void select(test::Node, cssom::Selector &selector,
  std::deque<test::Node> &selection)
{
  std::deque<test::Node> ret;

  selector.select((void*)&ret);

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
  cssom::CSSOM cssom;
  cssom::Selector selector = cssom.parseSelector("span");

  test::Node dom = test::Node::parse(
"<div>\n"
  "<p>Skip.</p>\n"
  "<span>Paragraph <span>with</span> spans.</span>\n"
  "<p>Skip.</p>\n"
"</div>\n"
  );

  std::deque<test::Node> selection;
  select(dom, selector, selection);

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
