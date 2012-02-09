lib_LTLIBRARIES = libcssom.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700 \
                 -I$(top_srcdir)/include

AM_CFLAGS = $(GENERIC_CFLAGS) -Werror



libcssom_ladir = $(includedir)

libcssom_la_HEADERS = ../include/cssom.h

libcssom_la_SOURCES = style_sheet.c



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif
