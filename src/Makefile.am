lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror



libcssom_base_ladir = $(includedir)

libcssom_base_la_HEADERS = $(top_srcdir)/include/cssom.h

libcssom_ladir = $(includedir)/cssom

libcssom_la_HEADERS = $(top_srcdir)/include/cssom/css_rule.h \
                      $(top_srcdir)/include/cssom/css_rule_list.h \
                      $(top_srcdir)/include/cssom/css_style_sheet.h \
                      $(top_srcdir)/include/cssom/style_sheet.h \
                      $(top_srcdir)/include/cssom/types.h

libcssom_la_SOURCES = style_sheet.c



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif
