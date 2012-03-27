lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror

top_idldir = $(top_srcdir)/idl
top_cssom_includedir = $(top_srcdir)/include/cssom



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_cssom_includedir)/CSSOM.h \
                      $(top_cssom_includedir)/CSSProperty.h \
                      $(top_cssom_includedir)/CSSRule.h \
                      $(top_cssom_includedir)/CSSRuleList.h \
                      $(top_cssom_includedir)/CSSStyleDeclaration.h \
                      $(top_cssom_includedir)/CSSStyleRule.h \
                      $(top_cssom_includedir)/CSSStyleSheet.h

libcssom_la_SOURCES = CSSEmitter.c \
                      CSSOM.c \
                      CSSProperty.c \
                      CSSRule.c \
                      CSSRuleList.c \
                      CSSStyleSheet.c \
                      Deque_CSSRule.c \
                      FSM_CSSProperty.c \
                      $(top_idldir)/CSSStyleDeclaration.idl

libcssom_la_LIBADD = $(SACC_LIBS)

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssom.pc



$(top_cssom_includedir)/CSSStyleDeclaration.h: $(top_idldir)/CSSStyleDeclaration.h
	cp $(top_idldir)/CSSStyleDeclaration.h $(top_cssom_includedir)/CSSStyleDeclaration.h



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif



include $(top_srcdir)/mk/idl.c.mk
