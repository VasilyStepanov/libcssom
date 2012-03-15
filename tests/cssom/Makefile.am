noinst_PROGRAMS = test_suite

AM_CFLAGS = -Wall -Wextra -Werror -ansi -pedantic -D_XOPEN_SOURCE=700 \
            -I$(top_srcdir)/include \
            $(SACC_CFLAGS)

test_suite_SOURCES = test_CSSOM.c \
                     test_CSSRule.c \
                     test_Deque.c \
                     test_List.c \
                     test_FSM.c \
                     test_Vector.c \
                     test_suite.c

test_suite_LDADD = $(top_srcdir)/src/libcssom.la



test: all
	./test_suite

.PHONY: test
