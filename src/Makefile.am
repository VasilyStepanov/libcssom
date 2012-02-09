lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_srcdir)/include/cssom/css_rule.h \
                      $(top_srcdir)/include/cssom/css_rule_list.h \
                      $(top_srcdir)/include/cssom/css_style_sheet.h \
                      $(top_srcdir)/include/cssom/types.h \
                      $(top_srcdir)/include/cssom/parser.h

libcssom_la_SOURCES = css_rule_list.c \
                      css_style_sheet.c \
                      parser.c

libcssom_la_LIBADD = $(SACC_LIBS)



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif
