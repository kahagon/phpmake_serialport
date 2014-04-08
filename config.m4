dnl
dnl $ Id: $
dnl

PHP_ARG_ENABLE(Gorilla, whether to enable Gorilla functions,
[  --enable-Gorilla         Enable Gorilla support])

if test "$PHP_GORILLA" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_GORILLA"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 50000
#error  this extension requires at least PHP version 5.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 5.0.0])])

  export CPPFLAGS="-Wno-return-type $OLD_CPPFLAGS"


  PHP_SUBST(GORILLA_SHARED_LIBADD)
  AC_DEFINE(HAVE_GORILLA, 1, [ ])

  PHP_NEW_EXTENSION(Gorilla, Gorilla.c GorillaPosix.c GorillaWin32.c, $ext_shared)

fi

