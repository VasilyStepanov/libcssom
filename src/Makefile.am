lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror

BUILT_SOURCES = $(top_idldir)/CSSPropertyValue.idl.h \
                $(top_idldir)/CSSRule.idl.h \
                $(top_idldir)/CSSRuleList.idl.h \
                $(top_idldir)/CSSStyleDeclaration.idl.h \
                $(top_idldir)/CSSStyleDeclarationValue.idl.h \
                $(top_idldir)/CSSStyleSheet.idl.h



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_srcdir)/include/cssom/CSSOM.h \
                      \
                      $(top_srcdir)/include/cssom/CSSFontFaceRule.h \
                      $(top_srcdir)/include/cssom/CSSImportRule.h \
                      $(top_srcdir)/include/cssom/CSSMediaRule.h \
                      $(top_srcdir)/include/cssom/CSSNamespaceRule.h \
                      $(top_srcdir)/include/cssom/CSSPageRule.h \
                      $(top_srcdir)/include/cssom/CSSPropertyValue.h \
                      $(top_srcdir)/include/cssom/CSSRule.h \
                      $(top_srcdir)/include/cssom/CSSRuleList.h \
                      $(top_srcdir)/include/cssom/CSSStyleDeclaration.h \
                      $(top_srcdir)/include/cssom/CSSStyleDeclarationValue.h \
                      $(top_srcdir)/include/cssom/CSSStyleRule.h \
                      $(top_srcdir)/include/cssom/CSSStyleSheet.h \
                      $(top_srcdir)/include/cssom/MediaList.h

libcssom_la_SOURCES = CSSEmitter.c \
                      CSSOM.c \
                      CSSPropertyData.c \
                      CSSPropertyType.c \
                      CSSPropertyValue.c \
                      CSSRule.c \
                      CSSRuleList.c \
                      CSSStyleDeclaration.c \
                      CSSStyleDeclarationValue.c \
                      CSSStyleSheet.c \
                      Deque_CSSRule.c \
                      Deque_MediaQuery.c \
                      Deque_void.c \
                      FSM_CSSPropertyValue.c \
                      LexicalUnitRange_azimuth.c \
                      LexicalUnitRange_background.c \
                      LexicalUnitRange_border.c \
                      LexicalUnitRange_bottom.c \
                      LexicalUnitRange_captionSide.c \
                      LexicalUnitRange_clear.c \
                      LexicalUnitRange_clip.c \
                      LexicalUnitRange_color.c \
                      LexicalUnitRange_content.c \
                      LexicalUnitRange_counter.c \
                      LexicalUnitRange_cue.c \
                      LexicalUnitRange_cursor.c \
                      LexicalUnitRange_direction.c \
                      LexicalUnitRange_display.c \
                      LexicalUnitRange_elevation.c \
                      LexicalUnitRange_emptyCells.c \
                      LexicalUnitRange_float.c \
                      LexicalUnitRange_utility.c \
                      MediaList.c \
                      MediaQuery.c \
                      Parser.c \
                      ParserStack.c \
                      ParserStats.c \
                      Sequence.c \
                      Selector.c \
                      memory.c

libcssom_la_LIBADD = $(SACC_LIBS)

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssom.pc



if ENABLE_PYWIDL
CLEANFILES = $(BUILT_SOURCES)
endif



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif



include $(top_srcdir)/mk/idl.h.mk
