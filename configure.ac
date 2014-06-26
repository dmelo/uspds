#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([t.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lGL':
AC_CHECK_LIB([GL], [main])
# FIXME: Replace `main' with a function in `-lglut':
AC_CHECK_LIB([glut], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])
# FIXME: Replace `main' with a function in `-lrevel':
AC_CHECK_LIB([revel], [main])
# FIXME: Replace `main' with a function in `-lxvidcore':
AC_CHECK_LIB([xvidcore], [main])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h malloc.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero ftruncate gethostbyaddr gethostbyname gettimeofday memset pow socket sqrt strerror strncasecmp strstr])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/eyes_java/Makefile
                 src/eyes_opengl/Makefile
                 src/lib/Makefile
                 src/lib/mathud/Makefile
                 src/revel/Makefile
                 src/simulator/Makefile
                 src/teste/Makefile])
AC_OUTPUT
