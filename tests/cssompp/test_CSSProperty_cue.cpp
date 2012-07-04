#include "test_CSSProperty_cue.hpp"

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



void cueAfter() {
  
  /**
   * <uri> | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cueAfter() == NULL);



  /**
   * <uri>
   */

  style.setCueAfter(NULL);
  style.setCueAfter("url('http://example.com/')");
  assertEquals(std::string("url(\"http://example.com/\")"), style.cueAfter());

  style.setCueAfter(NULL);
  style.setCueAfter("URL('HTTP://EXAMPLE.COM/')");
  assertEquals(std::string("url(\"HTTP://EXAMPLE.COM/\")"), style.cueAfter());



  /**
   * none
   */

  style.setCueAfter(NULL);
  style.setCueAfter("none");
  assertEquals(std::string("none"), style.cueAfter());

  style.setCueAfter(NULL);
  style.setCueAfter("NONE");
  assertEquals(std::string("none"), style.cueAfter());



  /**
   * inherit
   */

  style.setCueAfter(NULL);
  style.setCueAfter("inherit");
  assertEquals(std::string("inherit"), style.cueAfter());

  style.setCueAfter(NULL);
  style.setCueAfter("INHERIT");
  assertEquals(std::string("inherit"), style.cueAfter());



  /**
   * errors
   */

  style.setCueAfter(NULL);
  style.setCueAfter("invalid");
  assert(style.cueAfter() == NULL);
}



void cueBefore() {
  
  /**
   * <uri> | none | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cueBefore() == NULL);



  /**
   * <uri>
   */

  style.setCueBefore(NULL);
  style.setCueBefore("url('http://example.com/')");
  assertEquals(std::string("url(\"http://example.com/\")"), style.cueBefore());

  style.setCueBefore(NULL);
  style.setCueBefore("URL('HTTP://EXAMPLE.COM/')");
  assertEquals(std::string("url(\"HTTP://EXAMPLE.COM/\")"), style.cueBefore());



  /**
   * none
   */

  style.setCueBefore(NULL);
  style.setCueBefore("none");
  assertEquals(std::string("none"), style.cueBefore());

  style.setCueBefore(NULL);
  style.setCueBefore("NONE");
  assertEquals(std::string("none"), style.cueBefore());



  /**
   * inherit
   */

  style.setCueBefore(NULL);
  style.setCueBefore("inherit");
  assertEquals(std::string("inherit"), style.cueBefore());

  style.setCueBefore(NULL);
  style.setCueBefore("INHERIT");
  assertEquals(std::string("inherit"), style.cueBefore());



  /**
   * errors
   */

  style.setCueBefore(NULL);
  style.setCueBefore("invalid");
  assert(style.cueBefore() == NULL);
}



void cue() {
  
  /**
   * [ 'cue-before' || 'cue-after' ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cue() != NULL);
  assertEquals(std::string(""), style.cue());



  /**
   * 'cue-before'
   */

  style.setCue(NULL);
  style.setCue("url('http://example.com/')");
  assertEquals(std::string("url(\"http://example.com/\")"), style.cue());
  assertEquals(std::string("url(\"http://example.com/\")"), style.cueBefore());
  assertEquals(std::string("url(\"http://example.com/\")"), style.cueAfter());



  /**
   * 'cue-before' || 'cue-after'
   */

  style.setCue(NULL);
  style.setCue("url('http://example.com/before') "
    "url('http://example.com/after')");
  assertEquals(std::string("url(\"http://example.com/before\") "
    "url(\"http://example.com/after\")"), style.cue());
  assertEquals(std::string("url(\"http://example.com/before\")"),
    style.cueBefore());
  assertEquals(std::string("url(\"http://example.com/after\")"),
    style.cueAfter());

  style.setCue(NULL);
  style.setCue("NONE");
  assertEquals(std::string("none"), style.cue());



  /**
   * inherit
   */

  style.setCue(NULL);
  style.setCue("inherit");
  assertEquals(std::string("inherit"), style.cue());

  style.setCue(NULL);
  style.setCue("INHERIT");
  assertEquals(std::string("inherit"), style.cue());



  /**
   * errors
   */

  style.setCue(NULL);
  style.setCue("invalid");
  assertEquals(std::string(""), style.cue());
  assert(style.cueBefore() == NULL);
  assert(style.cueAfter() == NULL);

  style.setCue(NULL);
  style.setCue("none none none");
  assertEquals(std::string(""), style.cue());
  assert(style.cueBefore() == NULL);
  assert(style.cueAfter() == NULL);

  style.setCue(NULL);
  style.setCue("inherit inherit inherit");
  assertEquals(std::string(""), style.cue());
  assert(style.cueBefore() == NULL);
  assert(style.cueAfter() == NULL);
}



void shorthand() {
  
  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cue() != NULL);
  assertEquals(std::string(""), style.cue());



  /**
   * omit
   */

  style.setCue(NULL);
  style.setCueBefore("none");
  assertEquals(std::string(""), style.cue());
  assertEquals(std::string("none"), style.cueBefore());
  assert(style.cueAfter() == NULL);

  style.setCueAfter("none");
  assertEquals(std::string("none"), style.cue());
  assertEquals(std::string("none"), style.cueBefore());
  assertEquals(std::string("none"), style.cueAfter());

  style.setCueAfter("url(http://example.com/)");
  assertEquals(std::string("none url(\"http://example.com/\")"), style.cue());
  assertEquals(std::string("none"), style.cueBefore());
  assertEquals(std::string("url(\"http://example.com/\")"), style.cueAfter());




  /**
   * reset
   */

  style.setCue(NULL);
  assertEquals(std::string(""), style.cue());
  assert(style.cueBefore() == NULL);
  assert(style.cueAfter() == NULL);



  /**
   * inherit
   */

  style.setCue(NULL);
  style.setCue("inherit inherit");
  assertEquals(std::string("inherit"), style.cue());
  assertEquals(std::string("inherit"), style.cueBefore());
  assertEquals(std::string("inherit"), style.cueAfter());

  style.setCue(NULL);
  style.setCue("inherit");
  assertEquals(std::string("inherit"), style.cue());
  assertEquals(std::string("inherit"), style.cueBefore());
  assertEquals(std::string("inherit"), style.cueAfter());

  style.setCue(NULL);
  style.setCueBefore("inherit");
  style.setCueAfter("inherit");
  assertEquals(std::string("inherit"), style.cue());
  assertEquals(std::string("inherit"), style.cueBefore());
  assertEquals(std::string("inherit"), style.cueAfter());
}



} // unnamed

namespace test {



void cssPropertyCue() {
  cueAfter();
  cueBefore();
  cue();
  shorthand();
}



} // test
