lib_LTLIBRARIES = libcssompp.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CPPFLAGS = $(GENERIC_CFLAGS) -Werror



libcssompp_base_ladir = $(includedir)

libcssompp_base_la_HEADERS = $(top_srcdir)/include/cssompp.hpp

libcssompp_ladir = $(includedir)/cssom

libcssompp_la_HEADERS = $(top_srcdir)/include/cssompp/CSSOM.hpp

libcssompp_la_SOURCES = CSSOM.cpp \
                        CSSRuleList.cpp \
                        CSSStyleSheet.cpp

libcssompp_la_LIBADD = $(top_srcdir)/cssom-src/libcssom.la

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssompp.pc



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif
