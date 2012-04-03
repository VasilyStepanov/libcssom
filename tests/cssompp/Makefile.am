noinst_PROGRAMS = test_suite

AM_CPPFLAGS = -Wall -Wextra -Werror -ansi -pedantic -D_XOPEN_SOURCE=700 \
              -I$(top_srcdir)/include \
              $(SACC_CFLAGS)

test_suite_SOURCES = test_CSSOM.cpp \
                     test_suite.cpp

test_suite_LDADD = $(top_srcdir)/libcssompp/libcssompp.la



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
