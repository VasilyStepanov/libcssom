#include "test_CSSProperty_cursor.hpp"

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



void cursor() {
  
  /**
   * [ [<uri> ,]* [ auto | crosshair | default | pointer | move | e-resize |
   *  ne-resize | nw-resize | n-resize | se-resize | sw-resize | s-resize |
   *  w-resize | text | wait | help | progress ] ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.cursor() == NULL);



  /**
   * [ auto | crosshair | default | pointer | move | e-resize | ne-resize |
   *  nw-resize | n-resize | se-resize | sw-resize | s-resize | w-resize |
   *  text | wait | help | progress ]
   */

  style.setCursor(NULL);
  style.setCursor("auto");
  assertEquals(std::string("auto"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("crosshair");
  assertEquals(std::string("crosshair"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("default");
  assertEquals(std::string("default"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("pointer");
  assertEquals(std::string("pointer"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("move");
  assertEquals(std::string("move"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("e-resize");
  assertEquals(std::string("e-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("ne-resize");
  assertEquals(std::string("ne-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("nw-resize");
  assertEquals(std::string("nw-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("n-resize");
  assertEquals(std::string("n-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("se-resize");
  assertEquals(std::string("se-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("sw-resize");
  assertEquals(std::string("sw-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("s-resize");
  assertEquals(std::string("s-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("w-resize");
  assertEquals(std::string("w-resize"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("text");
  assertEquals(std::string("text"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("wait");
  assertEquals(std::string("wait"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("help");
  assertEquals(std::string("help"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("AUTO");
  assertEquals(std::string("auto"), style.cursor());



  /**
   * [<uri> ,]* [ auto | crosshair | default | pointer | move | e-resize |
   *  ne-resize | nw-resize | n-resize | se-resize | sw-resize | s-resize |
   *  w-resize | text | wait | help | progress ]
   */

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/'), auto");
  assertEquals(std::string("url(\"http://example.com/\"), auto"),
    style.cursor());

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/'), url('http://example.com/'), "
    "auto");
  assertEquals(std::string("url(\"http://example.com/\"), "
    "url(\"http://example.com/\"), auto"), style.cursor());



  /**
   * inherit
   */

  style.setCursor(NULL);
  style.setCursor("inherit");
  assertEquals(std::string("inherit"), style.cursor());

  style.setCursor(NULL);
  style.setCursor("INHERIT");
  assertEquals(std::string("inherit"), style.cursor());



  /**
   * errors
   */

  style.setCursor(NULL);
  style.setCursor("invalid");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/')");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/'),");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/') auto");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor(", auto");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/'), url('http://example.com/') "
    "auto");
  assert(style.cursor() == NULL);

  style.setCursor(NULL);
  style.setCursor("url('http://example.com/'), url('http://example.com/'), "
    "auto, url('http://example.com/')");
  assert(style.cursor() == NULL);
}



} // unnamed

namespace test {



void cssPropertyCursor() {
  cursor();
}



} // test
