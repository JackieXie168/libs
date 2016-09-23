#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([libcustl], [0.0.1], [jackie.CPlusPlus@gmail.com], [https://github.com/JackieXie168])
AC_CONFIG_SRCDIR([src/_list.c])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])

dnl Detect the canonical host and target build environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

# Checks for programs.
AC_LANG_CPLUSPLUS
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AM_PROG_CC_C_O
AM_PROG_LIBTOOL
AM_SANITY_CHECK

# Initialize libtool
LT_INIT

# Setup AM
AM_INIT_AUTOMAKE([foreign])
AM_PROG_CC_C_O
AM_PROG_LIBTOOL
AM_SANITY_CHECK

AC_CHECK_TOOL([STRIP],[strip])

################# LIBRARIES ####################################################

# Checks for libraries.

################### HEADERS ####################################################
# Checks for header files.
AC_HEADER_STDC
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h] ,[:] ,[missing_headers="$missing_headers $ac_header"])

if test ! -z "$missing_headers"; then
  AC_MSG_ERROR([missing headers: $missing_headers])
fi

# Checks for command line options

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_PID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_MODE_T

################### FUNCTIONS ##################################################
# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_FUNC_MKTIME
AC_CHECK_FUNCS([malloc memswp rand])

#################### FEATURES ##################################################
# Conditionals

##################### MODULES ##################################################
#
# Modules configuration
#

HostOS=`echo "$host" | sed 's/.*-//'`
os_is_macosx=false
nonLinuxOS=false
AC_SUBST(HostOS)
case ${HostOS} in
	darwin* | powerpc*-*-darwin* | freebsd* | netbsd* | openbsd*)
		userdefine_gethostbyname_r=true
		os_is_macosx=true
		nonLinuxOS=true
		echo HostOS="$HostOS"
		echo "userdefine_gethostbyname_r=true ..."
		;;
	*)
		echo host="$host"
		echo HostOS="$HostOS"
		os_is_macosx=false
		nonLinuxOS=false
		userdefine_gethostbyname_r=false
		echo "userdefine_gethostbyname_r=false ..."
		;;
esac		
AM_CONDITIONAL([USER_DEFINE_GETHOSTBYNAME_R], [test x$userdefine_gethostbyname_r = xtrue])
AM_COND_IF([USER_DEFINE_GETHOSTBYNAME_R],
	[AC_DEFINE([USER_DEFINE_GETHOSTBYNAME_R], [1], [Enable GETHOSTBYNAME_R module])])

AM_CONDITIONAL([IS_DARWIN], [test x$os_is_macosx = xtrue])
AM_COND_IF([IS_DARWIN],
	[AC_DEFINE([IS_DARWIN], [1], [Get HostOS Type is Darwin])])

AM_CONDITIONAL([NON_LINUX], [test x$userdefine_gethostbyname_r = xtrue])
AM_COND_IF([NON_LINUX],
	[AC_DEFINE([NON_LINUX], [1], [Get HostOS Type])])

##################### OPTIONAL CWMP METHODS ####################################
#
# Optional methods disable options
#

##################### FINAL CONFIGURATION ######################################
# Configure makefiles
AC_CONFIG_FILES([libcustl.pc
                 Makefile
                 src/Makefile
                 include/Makefile
                 ])

AC_OUTPUT
