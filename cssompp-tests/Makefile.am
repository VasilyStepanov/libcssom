noinst_PROGRAMS = test_suite

AM_CPPFLAGS = -Wall -Wextra -Werror -ansi -pedantic -D_XOPEN_SOURCE=700 \
              -I$(top_srcdir)/include \
              $(SACC_CFLAGS)

test_suite_SOURCES = test_CSSOM.cpp \
                     test_suite.cpp

test_suite_LDADD = $(top_srcdir)/cssompp-src/libcssompp.la



test: all
	./test_suite

.PHONY: test
