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

if test "x$tests_enabled" != "xno"; then
  PKG_CHECK_MODULES(LIBXML2, libxml-2.0)
fi



AC_ARG_ENABLE([memory-trace], [AS_HELP_STRING([--enable-memory-trace],
  [enable memory trace (DEVELOPERS ONLY)])],
  [memory_trace_enabled=$enableval],
  [memory_trace_enabled='no'])
AM_CONDITIONAL([ENABLE_MEMORY_TRACE], [test "x$memory_trace_enabled" != "xno"])
if test "x$memory_trace_enabled" != "xno"; then
  AC_DEFINE([ENABLE_MEMORY_TRACE], 1, [Memory trace (DEVELOPERS ONLY)])
fi



AC_ARG_ENABLE([pywidl], [AS_HELP_STRING([--enable-pywidl],
  [enable pywidl generator])],
  [pywidl_enabled=$enableval],
  [pywidl_enabled='no'])
if test "x$pywidl_enabled" != "xno"; then
  AC_CHECK_PYWIDL([0.1])
fi
AM_CONDITIONAL([ENABLE_PYWIDL], [test "x$pywidl_enabled" != "xno"])



PKG_CHECK_MODULES(SACC, sacc)



AC_CONFIG_FILES(
  [Makefile]
  [src/Makefile]
  [src/cssom.pc]
  [libcssompp/Makefile]
  [libcssompp/cssompp.pc]
  [tests/Makefile]
  [tests/cssom/Makefile]
  [tests/cssompp/Makefile]
)

AC_OUTPUT
