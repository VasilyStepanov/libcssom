#include "test_CSSFontFaceRule.hpp"
#include "test_CSSImportRule.hpp"
#include "test_CSSMediaRule.hpp"
#include "test_CSSNamespaceRule.hpp"
#include "test_CSSPageRule.hpp"
#include "test_CSSProperty_azimuth.hpp"
#include "test_CSSProperty_background.hpp"
#include "test_CSSProperty_border.hpp"
#include "test_CSSProperty_bottom.hpp"
#include "test_CSSProperty_captionSide.hpp"
#include "test_CSSProperty_clear.hpp"
#include "test_CSSProperty_clip.hpp"
#include "test_CSSProperty_color.hpp"
#include "test_CSSProperty_content.hpp"
#include "test_CSSProperty_counter.hpp"
#include "test_CSSProperty_cue.hpp"
#include "test_CSSProperty_cursor.hpp"
#include "test_CSSPropertyValue.hpp"
#include "test_CSSRule.hpp"
#include "test_CSSStyleDeclaration.hpp"
#include "test_CSSStyleDeclarationValue.hpp"
#include "test_CSSStyleRule.hpp"
#include "test_CSSStyleSheet.hpp"
#include "test_CSSOM.hpp"
#include "test_MediaList.hpp"
#include "test_Selector.hpp"



int main() {
  test::cssom();
  test::cssRule();
  test::cssStyleRule();
  test::cssPageRule();
  test::cssMediaRule();
  test::mediaList();
  test::cssNamespaceRule();
  test::cssFontFaceRule();
  test::cssImportRule();
  test::cssStyleSheet();
  test::cssStyleDeclaration();
  test::cssStyleDeclarationValue();
  test::cssPropertyValue();
  test::cssPropertyAzimuth();
  test::cssPropertyBackground();
  test::cssPropertyBorder();
  test::cssPropertyBottom();
  test::cssPropertyCaptionSide();
  test::cssPropertyClear();
  test::cssPropertyClip();
  test::cssPropertyColor();
  test::cssPropertyContent();
  test::cssPropertyCounter();
  test::cssPropertyCue();
  test::cssPropertyCursor();
  test::selector();
  return 0;
}
