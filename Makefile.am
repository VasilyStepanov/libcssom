if ENABLE_TESTS
  MAYBE_TESTS = tests
endif
SUBDIRS = src libcssompp $(MAYBE_TESTS)

ACLOCAL_AMFLAGS = -I m4



if ENABLE_TESTS
test: all
	make -C tests test

.PHONY: test
endif
