noinst_PROGRAMS = test_suite

AM_CPPFLAGS = -Wall -Wextra -Werror -ansi -pedantic -D_XOPEN_SOURCE=700 \
              -I$(top_srcdir)/include \
              $(LIBXML2_CFLAGS) \
              $(SACC_CFLAGS)

test_suite_SOURCES = Errors.cpp \
                     Node.cpp \
                     NodeImpl.cpp \
                     NodeList.cpp \
                     NodeListImpl.cpp \
                     test_CSSFontFaceRule.cpp \
                     test_CSSImportRule.cpp \
                     test_CSSMediaRule.cpp \
                     test_CSSNamespaceRule.cpp \
                     test_CSSOM.cpp \
                     test_CSSPageRule.cpp \
                     test_CSSProperty_azimuth.cpp \
                     test_CSSProperty_background.cpp \
                     test_CSSProperty_border.cpp \
                     test_CSSProperty_bottom.cpp \
                     test_CSSProperty_captionSide.cpp \
                     test_CSSProperty_clear.cpp \
                     test_CSSPropertyValue.cpp \
                     test_CSSRule.cpp \
                     test_CSSStyleDeclaration.cpp \
                     test_CSSStyleDeclarationValue.cpp \
                     test_CSSStyleRule.cpp \
                     test_CSSStyleSheet.cpp \
                     test_MediaList.cpp \
                     test_Selector.cpp \
                     test_suite.cpp

test_suite_LDADD = $(top_srcdir)/libcssompp/libcssompp.la \
                   $(LIBXML2_LIBS)


if ENABLE_MEMORY_TRACE



test: all
	$(RM) malloc free
	-./test_suite
	cat malloc | sort > smalloc
	cat free | sort > sfree



else



test: all
	./test_suite



endif

.PHONY: test
