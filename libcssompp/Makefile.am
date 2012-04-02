lib_LTLIBRARIES = libcssompp.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CPPFLAGS = $(GENERIC_CFLAGS) -Werror

BUILT_SOURCES = $(top_idldir)/CSSNamespaceRule.idl.hpp \
                $(top_idldir)/CSSRule.idl.hpp \
                $(top_idldir)/CSSRuleList.idl.hpp \
                $(top_idldir)/CSSStyleDeclaration.idl.hpp \
                $(top_idldir)/CSSStyleRule.idl.hpp \
                $(top_idldir)/CSSStyleSheet.idl.hpp



libcssompp_base_ladir = $(includedir)

libcssompp_base_la_HEADERS = $(top_srcdir)/include/cssompp.hpp

libcssompp_ladir = $(includedir)/cssom

libcssompp_la_HEADERS = $(top_srcdir)/include/cssompp/CSSOM.hpp \
                        \
                        $(top_srcdir)/include/cssompp/CSSNamespaceRule.hpp \
                        $(top_srcdir)/include/cssompp/CSSRule.hpp \
                        $(top_srcdir)/include/cssompp/CSSRuleList.hpp \
                        $(top_srcdir)/include/cssompp/CSSStyleDeclaration.hpp \
                        $(top_srcdir)/include/cssompp/CSSStyleRule.hpp \
                        $(top_srcdir)/include/cssompp/CSSStyleSheet.hpp

libcssompp_la_SOURCES = CSSOM.cpp \
                        CSSProperty.cpp \
                        \
                        CSSNamespaceRule.cpp \
                        CSSRule.cpp \
                        CSSStyleDeclaration.cpp \
                        CSSStyleRule.cpp \
                        CSSStyleSheet.cpp

libcssompp_la_LIBADD = $(top_srcdir)/src/libcssom.la

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssompp.pc



if ENABLE_PYWIDL
CLEANFILES = $(BUILT_SOURCES)
endif



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif



include $(top_srcdir)/mk/idl.cpp.mk
