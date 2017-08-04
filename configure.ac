AC_PREREQ([2.69])
AC_INIT([marble-solitaire], [0.1], [alan.wayne.johnson@gmail.com])
AC_CONFIG_SRCDIR([src/marble_solitaire.c])

AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror -Wno-portability])

AC_PROG_CC
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, [glib-compile-resources])

PKG_CHECK_MODULES([GTK], [gtk+-3.0])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
