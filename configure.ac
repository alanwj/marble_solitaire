AC_PREREQ([2.69])
AC_INIT([marble-solitaire], [0.1], [alan.wayne.johnson@gmail.com])
AC_CONFIG_SRCDIR([src/marble_solitaire.c])

AM_INIT_AUTOMAKE([foreign -Wall -Werror -Wno-portability])
AM_PATH_GTK_3_0

AC_PROG_CC
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, [glib-compile-resources])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
