#include "test_Selector.hpp"

#include "Errors.hpp"
#include "Node.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>
#include <cssompp/Selector.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



void selectorText() {
  std::string selectorText;
  cssom::CSSOM cssom;
  cssom::Selector selector = cssom.parseSelector("p");



  selectorText = "p";
  assertEquals(selectorText, selector.selectorText());
}



void selectElements() {
}



} // unnamed

namespace test {



void selector() {
  selectorText();
  selectElements();
}



} // test
