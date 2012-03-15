if ENABLE_TESTS
  MAYBE_TESTS = cssom-tests cssompp-tests
endif
SUBDIRS = src libcssompp $(MAYBE_TESTS)

ACLOCAL_AMFLAGS = -I m4



if ENABLE_TESTS
test: all
	make -C cssom-tests test
	make -C cssompp-tests test

.PHONY: test
endif
