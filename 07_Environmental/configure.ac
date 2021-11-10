#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [0.00], [lyuha1504@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([rhash is needed])])
AC_CHECK_LIB([readline],[readline])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])
AC_CHECK_HEADER([rhash.h],[],[],[AC_MSG_ERROR([cannot find rhash.h])])
AC_CHECK_HEADER([readline/readline.h])
AC_CHECK_HEADER([readline/history.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

# Check --enable-readline option
AC_ARG_ENABLE([readline],
	AS_HELP_STRING([--enable-readline], [Enable the use of readline instead of getline]),
	AC_DEFINE(USE_READLINE,[],[Readline usage])
	)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
