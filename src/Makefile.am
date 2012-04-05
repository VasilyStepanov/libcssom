lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror

BUILT_SOURCES = $(top_idldir)/CSSNamespaceRule.idl.h \
                $(top_idldir)/CSSPageRule.idl.h \
                $(top_idldir)/CSSRule.idl.h \
                $(top_idldir)/CSSRuleList.idl.h \
                $(top_idldir)/CSSStyleDeclaration.idl.h \
                $(top_idldir)/CSSStyleRule.idl.h \
                $(top_idldir)/CSSStyleSheet.idl.h



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_srcdir)/include/cssom/CSSOM.h \
                      $(top_srcdir)/include/cssom/CSSProperty.h \
                      \
                      $(top_srcdir)/include/cssom/CSSNamespaceRule.h \
                      $(top_srcdir)/include/cssom/CSSPageRule.h \
                      $(top_srcdir)/include/cssom/CSSRule.h \
                      $(top_srcdir)/include/cssom/CSSRuleList.h \
                      $(top_srcdir)/include/cssom/CSSStyleDeclaration.h \
                      $(top_srcdir)/include/cssom/CSSStyleRule.h \
                      $(top_srcdir)/include/cssom/CSSStyleSheet.h

libcssom_la_SOURCES = CSSEmitter.c \
                      CSSOM.c \
                      CSSProperty.c \
                      CSSRule.c \
                      CSSStyleSheet.c \
                      Deque_CSSRule.c \
                      Deque_void.c \
                      FSM_CSSProperty.c \
                      CSSStyleDeclaration.c \
                      Sequence.c \
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



include $(top_srcdir)/mk/idl.c.mk
