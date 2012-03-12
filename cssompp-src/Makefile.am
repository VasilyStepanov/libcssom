lib_LTLIBRARIES = libcssompp.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic \
                 -I$(top_srcdir)/include

AM_CPPFLAGS = $(GENERIC_CFLAGS) -Werror



libcssompp_base_ladir = $(includedir)

libcssompp_base_la_HEADERS = $(top_srcdir)/include/cssompp.h

libcssompp_ladir = $(includedir)/cssom

libcssompp_la_HEADERS = $(top_srcdir)/include/cssompp/CSSOM.h

libcssompp_la_SOURCES = CSSOM.cpp

libcssompp_la_LIBADD = $(SACC_LIBS)

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssompp.pc



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif
