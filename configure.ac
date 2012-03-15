AC_INIT([libcssom], [0.0])
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER([config.h])

AC_PROG_CC
AC_PROG_CXX

LT_INIT

AC_CONFIG_MACRO_DIR([m4])



AC_ARG_ENABLE([tests], [AS_HELP_STRING([--enable-tests],
  [enable testing code])],
  [tests_enabled=$enableval],
  [tests_enabled='no'])
AM_CONDITIONAL([ENABLE_TESTS], [test "x$tests_enabled" != "xno"])

PKG_CHECK_MODULES(SACC, sacc)



AC_CONFIG_FILES(
  [Makefile]
  [src/Makefile]
  [src/cssom.pc]
  [libcssompp/Makefile]
  [libcssompp/cssompp.pc]
  [cssom-tests/Makefile]
  [cssompp-tests/Makefile]
)

AC_OUTPUT
