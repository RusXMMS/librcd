dnl Process this file with autoconf to produce a configure script.
AC_INIT(librcd, m4_esyscmd([head -n 1 VERSION | sed -e s/CVS.*$// | tr -d \\n]))
AC_CONFIG_SRCDIR([src/librcd.c])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE()
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

PACKAGE=librcd
LIBRCD_VERSION_MAJOR=`cat VERSION | sed -e s/CVS// | cut -d . -f 1 | sed -e s/^$/0/`
LIBRCD_VERSION_MINOR=`cat VERSION | sed -e s/CVS// | cut -d . -f 2 | sed -e s/^$/0/`
LIBRCD_VERSION_SUBMINOR=`cat VERSION | sed -e s/CVS// | cut -d . -f 3 | sed -e s/^$/0/`
LIBRCD_VERSION=$LIBRCD_VERSION_MAJOR.$LIBRCD_VERSION_MINOR.$LIBRCD_VERSION_SUBMINOR
LIBRCD_VERSION_INFO=`echo $LIBRCD_VERSION | awk -F. '{ printf "%d:%d:%d", $1+$2, $3, $2 }'`

AC_SUBST(LIBRCD_VERSION)
AC_SUBST(LIBRCD_VERSION_MAJOR)
AC_SUBST(LIBRCD_VERSION_MINOR)
AC_SUBST(LIBRCD_VERSION_SUBMINOR)
AC_SUBST(LIBRCD_VERSION_INFO)

AC_ARG_ENABLE( latin,
    [  --disable-latin		disable detection of ISO-8859-1],,
    disable_latin="yes")

if test "x$disable_latin" = "xyes"; then
    AC_DEFINE(DETECT_LATIN,1,[Defines if ISO-8859-1 detection is enabled])
fi

AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_LIBTOOL

AC_PATH_PROG(RM, rm, /bin/rm)
AC_PATH_PROG(MV, mv, /bin/mv)
AC_PATH_PROG(TAR, tar, /bin/tar)

dnl Fixing ugly libtool, see for details
dnl http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=523750
RM="$RM -f"


dnl Checks for programs.

dnl Checks for libraries.

dnl Checks for header files.

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

dnl Checks for library functions.

AC_OUTPUT(src/Makefile examples/Makefile statgen/Makefile Makefile librcd.spec librcd.pc)
