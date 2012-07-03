#include "test_CSSProperty_counter.hpp"

#include "Errors.hpp"
#include "utility.hpp"

#include <cssompp/CSSOM.hpp>
#include <cssompp/CSSStyleDeclaration.hpp>
#include <cssompp/CSSStyleRule.hpp>
#include <cssompp/CSSStyleSheet.hpp>

#include <iostream>
#include <stdexcept>

#include <assert.h>

namespace {



cssom::CSSStyleDeclaration getStyleDeclaration(const cssom::CSSOM &cssom) {
  return cssom::CSSStyleRule::cast(cssom.parse("p {}").cssRules()[0]).style();
}



void counterIncrement() {
  
  /**
   * [ <identifier> <integer>? ]+ | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.counterIncrement() == NULL);



  /**
   * [ <identifier> ]+
   */

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter");
  assertEquals(std::string("chapter"), style.counterIncrement());

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter SECTION");
  assertEquals(std::string("chapter section"), style.counterIncrement());



  /**
   * [ <identifier> <integer>? ]+
   */

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter 3");
  assertEquals(std::string("chapter 3"), style.counterIncrement());

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter 3 section 2");
  assertEquals(std::string("chapter 3 section 2"), style.counterIncrement());

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter section 2");
  assertEquals(std::string("chapter section 2"), style.counterIncrement());



  /**
   * none
   */

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("none");
  assertEquals(std::string("none"), style.counterIncrement());

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("NONE");
  assertEquals(std::string("none"), style.counterIncrement());



  /**
   * inherit
   */

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("inherit");
  assertEquals(std::string("inherit"), style.counterIncrement());

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("INHERIT");
  assertEquals(std::string("inherit"), style.counterIncrement());



  /**
   * errors
   */

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("none 2");
  assert(style.counterIncrement() == NULL);

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("none inherit");
  assert(style.counterIncrement() == NULL);

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("inherit 2");
  assert(style.counterIncrement() == NULL);

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter 2.1");
  assert(style.counterIncrement() == NULL);

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("chapter 2 1");
  assert(style.counterIncrement() == NULL);

  style.setCounterIncrement(NULL);
  style.setCounterIncrement("2 chapter 1");
  assert(style.counterIncrement() == NULL);
}



void counterReset() {
  
  /**
   * [ <identifier> <integer>? ]+ | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.counterReset() == NULL);



  /**
   * [ <identifier> ]+
   */

  style.setCounterReset(NULL);
  style.setCounterReset("chapter");
  assertEquals(std::string("chapter"), style.counterReset());

  style.setCounterReset(NULL);
  style.setCounterReset("chapter SECTION");
  assertEquals(std::string("chapter section"), style.counterReset());



  /**
   * [ <identifier> <integer>? ]+
   */

  style.setCounterReset(NULL);
  style.setCounterReset("chapter 3");
  assertEquals(std::string("chapter 3"), style.counterReset());

  style.setCounterReset(NULL);
  style.setCounterReset("chapter 3 section 2");
  assertEquals(std::string("chapter 3 section 2"), style.counterReset());

  style.setCounterReset(NULL);
  style.setCounterReset("chapter section 2");
  assertEquals(std::string("chapter section 2"), style.counterReset());



  /**
   * none
   */

  style.setCounterReset(NULL);
  style.setCounterReset("none");
  assertEquals(std::string("none"), style.counterReset());

  style.setCounterReset(NULL);
  style.setCounterReset("NONE");
  assertEquals(std::string("none"), style.counterReset());



  /**
   * inherit
   */

  style.setCounterReset(NULL);
  style.setCounterReset("inherit");
  assertEquals(std::string("inherit"), style.counterReset());

  style.setCounterReset(NULL);
  style.setCounterReset("INHERIT");
  assertEquals(std::string("inherit"), style.counterReset());



  /**
   * errors
   */

  style.setCounterReset(NULL);
  style.setCounterReset("none 2");
  assert(style.counterReset() == NULL);

  style.setCounterReset(NULL);
  style.setCounterReset("none inherit");
  assert(style.counterReset() == NULL);

  style.setCounterReset(NULL);
  style.setCounterReset("inherit 2");
  assert(style.counterReset() == NULL);

  style.setCounterReset(NULL);
  style.setCounterReset("chapter 2.1");
  assert(style.counterReset() == NULL);

  style.setCounterReset(NULL);
  style.setCounterReset("chapter 2 1");
  assert(style.counterReset() == NULL);

  style.setCounterReset(NULL);
  style.setCounterReset("2 chapter 1");
  assert(style.counterReset() == NULL);
}



} // unnamed

namespace test {



void cssPropertyCounter() {
  counterIncrement();
  counterReset();
}



} // test
