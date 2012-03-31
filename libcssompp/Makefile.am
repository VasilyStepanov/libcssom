lib_LTLIBRARIES = libcssompp.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CPPFLAGS = $(GENERIC_CFLAGS) -Werror

BUILT_SOURCES = $(top_idldir)/CSSRule.idl.hpp \
                $(top_idldir)/CSSStyleDeclaration.idl.hpp \
                $(top_idldir)/CSSStyleRule.idl.hpp



libcssompp_base_ladir = $(includedir)

libcssompp_base_la_HEADERS = $(top_srcdir)/include/cssompp.hpp

libcssompp_ladir = $(includedir)/cssom

libcssompp_la_HEADERS = $(top_srcdir)/include/cssompp/CSSOM.hpp \
                        \
                        $(top_srcdir)/include/cssompp/CSSRule.hpp \
                        $(top_srcdir)/include/cssompp/CSSStyleDeclaration.hpp \
                        $(top_srcdir)/include/cssompp/CSSStyleRule.hpp

libcssompp_la_SOURCES = CSSOM.cpp \
                        CSSProperty.cpp \
                        CSSStyleSheet.cpp \
                        \
                        CSSRule.cpp \
                        CSSStyleDeclaration.cpp \
                        CSSStyleRule.cpp

libcssompp_la_LIBADD = $(top_srcdir)/src/libcssom.la

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssompp.pc



CLEANFILES = $(BUILT_SOURCES)



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif



include $(top_srcdir)/mk/idl.cpp.mk
