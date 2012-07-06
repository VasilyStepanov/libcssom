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



void fontSize() {
  
  /**
   * <absolute-size> | <relative-size> | <length> | <percentage> | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.fontSize() == NULL);



  /**
   * <absolute-size>
   */

  style.setFontSize(NULL);
  style.setFontSize("xx-small");
  assertEquals(std::string("xx-small"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("x-small");
  assertEquals(std::string("x-small"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("small");
  assertEquals(std::string("small"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("medium");
  assertEquals(std::string("medium"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("large");
  assertEquals(std::string("large"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("x-large");
  assertEquals(std::string("x-large"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("xx-large");
  assertEquals(std::string("xx-large"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("XX-SMALL");
  assertEquals(std::string("xx-small"), style.fontSize());



  /**
   * <relative-size>
   */

  style.setFontSize(NULL);
  style.setFontSize("larger");
  assertEquals(std::string("larger"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("smaller");
  assertEquals(std::string("smaller"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("LARGER");
  assertEquals(std::string("larger"), style.fontSize());



  /**
   * <length>
   */

  style.setFontSize(NULL);
  style.setFontSize("12pt");
  assertEquals(std::string("12pt"), style.fontSize());



  /**
   * <percentage>
   */

  style.setFontSize(NULL);
  style.setFontSize("150%");
  assertEquals(std::string("150%"), style.fontSize());



  /**
   * inherit
   */

  style.setFontSize(NULL);
  style.setFontSize("inherit");
  assertEquals(std::string("inherit"), style.fontSize());

  style.setFontSize(NULL);
  style.setFontSize("INHERIT");
  assertEquals(std::string("inherit"), style.fontSize());



  /**
   * errors
   */

  style.setFontSize(NULL);
  style.setFontSize("invalid");
  assert(style.fontSize() == NULL);

  style.setFontSize(NULL);
  style.setFontSize("-1em");
  assert(style.fontSize() == NULL);

  style.setFontSize(NULL);
  style.setFontSize("-10%");
  assert(style.fontSize() == NULL);
}



void fontStyle() {
  
  /**
   * normal | italic | oblique | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.fontStyle() == NULL);



  /**
   * normal | italic | oblique
   */

  style.setFontStyle(NULL);
  style.setFontStyle("normal");
  assertEquals(std::string("normal"), style.fontStyle());

  style.setFontStyle(NULL);
  style.setFontStyle("italic");
  assertEquals(std::string("italic"), style.fontStyle());

  style.setFontStyle(NULL);
  style.setFontStyle("oblique");
  assertEquals(std::string("oblique"), style.fontStyle());

  style.setFontStyle(NULL);
  style.setFontStyle("NORMAL");
  assertEquals(std::string("normal"), style.fontStyle());



  /**
   * inherit
   */

  style.setFontStyle(NULL);
  style.setFontStyle("inherit");
  assertEquals(std::string("inherit"), style.fontStyle());

  style.setFontStyle(NULL);
  style.setFontStyle("INHERIT");
  assertEquals(std::string("inherit"), style.fontStyle());



  /**
   * errors
   */

  style.setFontStyle(NULL);
  style.setFontStyle("invalid");
  assert(style.fontStyle() == NULL);
}



void fontVariant() {
  
  /**
   * normal | small-caps | inherit
   */

  cssom::CSSOM cssom;
  cssom::CSSStyleDeclaration style = getStyleDeclaration(cssom);

  assert(style.fontVariant() == NULL);



  /**
   * normal | small-caps
   */

  style.setFontVariant(NULL);
  style.setFontVariant("normal");
  assertEquals(std::string("normal"), style.fontVariant());

  style.setFontVariant(NULL);
  style.setFontVariant("small-caps");
  assertEquals(std::string("small-caps"), style.fontVariant());

  style.setFontVariant(NULL);
  style.setFontVariant("NORMAL");
  assertEquals(std::string("normal"), style.fontVariant());



  /**
   * inherit
   */

  style.setFontVariant(NULL);
  style.setFontVariant("inherit");
  assertEquals(std::string("inherit"), style.fontVariant());

  style.setFontVariant(NULL);
  style.setFontVariant("INHERIT");
  assertEquals(std::string("inherit"), style.fontVariant());



  /**
   * errors
   */

  style.setFontVariant(NULL);
  style.setFontVariant("invalid");
  assert(style.fontVariant() == NULL);
}



} // unnamed

namespace test {



void cssPropertyFont() {
  fontFamily();
  fontSize();
  fontStyle();
  fontVariant();
}



} // test
