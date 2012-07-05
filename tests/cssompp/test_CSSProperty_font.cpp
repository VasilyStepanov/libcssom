#include "test_CSSProperty_font.hpp"

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



void fontFamily() {
  
  /**
   * [[ <family-name> | <generic-family> ] [, <family-name> |
   *  <generic-family>]* ] | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.fontFamily() == NULL);



  /**
   * <generic-family>
   */

  style.setFontFamily(NULL);
  style.setFontFamily("serif");
  assertEquals(std::string("serif"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("sans-serif");
  assertEquals(std::string("sans-serif"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("cursive");
  assertEquals(std::string("cursive"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("fantasy");
  assertEquals(std::string("fantasy"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("monospace");
  assertEquals(std::string("monospace"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("SERIF");
  assertEquals(std::string("serif"), style.fontFamily());



  /**
   * [[ <family-name> | <generic-family> ] [, <family-name> |
   *  <generic-family>]* ]
   */

  style.setFontFamily(NULL);
  style.setFontFamily("Gill, Helvetica, sans-serif");
  assertEquals(std::string("gill, helvetica, sans-serif"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("'quoted as strings'");
  assertEquals(std::string("\"quoted as strings\""), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("unquoted as a sequence of one or more identifiers");
  assertEquals(std::string("unquoted as a sequence of one or more identifiers"),
    style.fontFamily());



  /**
   * inherit
   */

  style.setFontFamily(NULL);
  style.setFontFamily("inherit");
  assertEquals(std::string("inherit"), style.fontFamily());

  style.setFontFamily(NULL);
  style.setFontFamily("INHERIT");
  assertEquals(std::string("inherit"), style.fontFamily());



  /**
   * errors
   */

  style.setFontFamily(NULL);
  style.setFontFamily("Red/Black, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("\"Lucida\" Grande, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("Ahem!, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("test@foo, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("#POUND, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("Hawaii 5-0, sans-serif");
  assert(style.fontFamily() == NULL);

  style.setFontFamily(NULL);
  style.setFontFamily("serif bar");
  assert(style.fontFamily() == NULL);

  /**
   * TODO: no idea how to handle this.
   */
  style.setFontFamily(NULL);
  style.setFontFamily("foo serif bar");
  assertEquals(std::string("foo serif bar"), style.fontFamily());
}



} // unnamed

namespace test {



void cssPropertyFont() {
  fontFamily();
}



} // test
