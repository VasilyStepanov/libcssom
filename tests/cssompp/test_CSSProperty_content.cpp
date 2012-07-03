#include "test_CSSProperty_content.hpp"

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



void content() {
  
  /**
   * normal | none | [ <string> | <uri> | <counter> | attr(<identifier>) |
   *  open-quote | close-quote | no-open-quote | no-close-quote ]+ | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.content() == NULL);



  /**
   * normal
   */

  style.setContent(NULL);
  style.setContent("normal");
  assertEquals(std::string("normal"), style.content());

  style.setContent(NULL);
  style.setContent("NORMAL");
  assertEquals(std::string("normal"), style.content());



  /**
   * none
   */

  style.setContent(NULL);
  style.setContent("none");
  assertEquals(std::string("none"), style.content());

  style.setContent(NULL);
  style.setContent("NONE");
  assertEquals(std::string("none"), style.content());



  /**
   * [ <string> ]+
   */

  style.setContent(NULL);
  style.setContent("'whatever' 'WHATEVER'");
  assertEquals(std::string("\"whatever\" \"WHATEVER\""), style.content());



  /**
   * [ <uri> ]+
   */

  style.setContent(NULL);
  style.setContent("url('http://example.com/') URL('HTTP://EXAMPLE.COM/')");
  assertEquals(std::string("url(\"http://example.com/\") "
    "url(\"HTTP://EXAMPLE.COM/\")"), style.content());



  /**
   * [ <counter> ]+
   */

  style.setContent(NULL);
  style.setContent("counter(whatever) COUNTER(WHATEVER, upper-roman)");
  assertEquals(std::string(
    "counter(whatever) counter(whatever, upper-roman)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, disc)");
  assertEquals(std::string("counter(whatever, disc)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, circle)");
  assertEquals(std::string("counter(whatever, circle)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, square)");
  assertEquals(std::string("counter(whatever, square)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, decimal-leading-zero)");
  assertEquals(std::string("counter(whatever, decimal-leading-zero)"),
    style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, lower-roman)");
  assertEquals(std::string("counter(whatever, lower-roman)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, upper-roman)");
  assertEquals(std::string("counter(whatever, upper-roman)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, lower-greek)");
  assertEquals(std::string("counter(whatever, lower-greek)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, lower-latin)");
  assertEquals(std::string("counter(whatever, lower-latin)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, upper-latin)");
  assertEquals(std::string("counter(whatever, upper-latin)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, armenian)");
  assertEquals(std::string("counter(whatever, armenian)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, georgian)");
  assertEquals(std::string("counter(whatever, georgian)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, lower-alpha)");
  assertEquals(std::string("counter(whatever, lower-alpha)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, upper-alpha)");
  assertEquals(std::string("counter(whatever, upper-alpha)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, none)");
  assertEquals(std::string("counter(whatever, none)"), style.content());

  style.setContent(NULL);
  style.setContent("counter(whatever, NONE)");
  assertEquals(std::string("counter(whatever, none)"), style.content());



  /**
   * [ attr(<identifier>) ]+
   */

  style.setContent(NULL);
  style.setContent("attr(whatever) ATTR(WHATEVER)");
  assertEquals(std::string("attr(whatever) attr(whatever)"), style.content());



  /**
   * [ open-quote ]+
   */

  style.setContent(NULL);
  style.setContent("open-quote OPEN-QUOTE");
  assertEquals(std::string("open-quote open-quote"), style.content());



  /**
   * [ close-quote ]+
   */

  style.setContent(NULL);
  style.setContent("close-quote CLOSE-QUOTE");
  assertEquals(std::string("close-quote close-quote"), style.content());



  /**
   * [ no-open-quote ]+
   */

  style.setContent(NULL);
  style.setContent("no-open-quote NO-OPEN-QUOTE");
  assertEquals(std::string("no-open-quote no-open-quote"), style.content());



  /**
   * [ no-close-quote ]+
   */

  style.setContent(NULL);
  style.setContent("no-close-quote NO-CLOSE-QUOTE");
  assertEquals(std::string("no-close-quote no-close-quote"), style.content());



  /**
   * [ <string> | <uri> | <counter> | attr(<identifier>) |
   *  open-quote | close-quote | no-open-quote | no-close-quote ]+
   */

  style.setContent(NULL);
  style.setContent("attr(whatever) 'string' counter(whatever) url('example') "
    "no-open-quote close-quote open-quote no-close-quote attr(again)");
  assertEquals(std::string("attr(whatever) \"string\" counter(whatever) "
    "url(\"example\") no-open-quote close-quote open-quote "
    "no-close-quote attr(again)"), style.content());



  /**
   * inherit
   */

  style.setContent(NULL);
  style.setContent("inherit");
  assertEquals(std::string("inherit"), style.content());

  style.setContent(NULL);
  style.setContent("INHERIT");
  assertEquals(std::string("inherit"), style.content());



  /**
   * errors
   */

  style.setContent(NULL);
  style.setContent("invalid");
  assert(style.content() == NULL);

  style.setContent(NULL);
  style.setContent("attr('error')");
  assert(style.content() == NULL);

  style.setContent(NULL);
  style.setContent("counter('error')");
  assert(style.content() == NULL);

  style.setContent(NULL);
  style.setContent("normal none");
  assert(style.content() == NULL);

  style.setContent(NULL);
  style.setContent("normal 'error'");
  assert(style.content() == NULL);

  style.setContent(NULL);
  style.setContent("counter(whatever, error)");
  assert(style.content() == NULL);
}



} // unnamed

namespace test {



void cssPropertyContent() {
  content();
}



} // test
