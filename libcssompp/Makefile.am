lib_LTLIBRARIES = libcssompp.la

GENERIC_CFLAGS = -Wall -Wextra -ansi -pedantic \
                 -I$(top_srcdir)/include \
                 $(SACC_CFLAGS)

AM_CPPFLAGS = $(GENERIC_CFLAGS) -Werror

top_idldir = $(top_srcdir)/idl
top_cssompp_includedir = $(top_srcdir)/include/cssompp



libcssompp_base_ladir = $(includedir)

libcssompp_base_la_HEADERS = $(top_srcdir)/include/cssompp.hpp

libcssompp_ladir = $(includedir)/cssom

libcssompp_la_HEADERS = $(top_cssompp_includedir)/CSSOM.hpp \
                        $(top_cssompp_includedir)/CSSStyleDeclaration.hpp

libcssompp_la_SOURCES = CSSOM.cpp \
                        CSSProperty.cpp \
                        CSSRule.cpp \
                        CSSRuleList.cpp \
                        CSSStyleRule.cpp \
                        CSSStyleSheet.cpp \
                        $(top_idldir)/CSSStyleDeclaration.idl

libcssompp_la_LIBADD = $(top_srcdir)/src/libcssom.la

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cssompp.pc




$(top_cssompp_includedir)/CSSStyleDeclaration.hpp: $(top_idldir)/CSSStyleDeclaration.hpp
	cp $(top_idldir)/CSSStyleDeclaration.hpp $(top_cssompp_includedir)/CSSStyleDeclaration.hpp



clean-local:
	$(RM) $(top_idldir)/*.hpp $(top_idldir)/*.cpp



if ENABLE_TESTS
test: all
	make -C $(top_srcdir)/tests test

.PHONY: test
endif



include $(top_srcdir)/mk/idl.cpp.mk
