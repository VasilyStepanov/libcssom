lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_srcdir)/include/cssom/CSSOM.h \
                      $(top_srcdir)/include/cssom/CSSProperty.h \
                      $(top_srcdir)/include/cssom/CSSRule.h \
                      $(top_srcdir)/include/cssom/CSSRuleList.h \
                      $(top_srcdir)/include/cssom/CSSStyleDeclaration.h \
                      $(top_srcdir)/include/cssom/CSSStyleRule.h \
                      $(top_srcdir)/include/cssom/CSSStyleSheet.h

libcssom_la_SOURCES = CSSEmitter.c \
                      CSSOM.c \
                      CSSProperty.c \
                      CSSRule.c \
                      CSSRuleList.c \
                      CSSStyleDeclaration.c \
                      CSSStyleSheet.c \
                      Deque_CSSRule.c \
                      FSM_CSSProperty.c

libcssom_la_LIBADD = $(SACC_LIBS)

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssom.pc



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/cssom-tests test

.PHONY: test
endif
