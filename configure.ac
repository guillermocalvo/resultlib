#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


# Autoconf requirements
AC_PREREQ([2.68])


# Initialize package
AC_INIT([result], [1.0.0], [result@guillermo.dev], [result], [https://github.com/guillermocalvo/resultlib/])


# Information on the package
AC_COPYRIGHT([Copyright 2025 Guillermo Calvo])
AC_REVISION([$PACKAGE_VERSION])
AC_MSG_NOTICE([
     ____                 _ _
    |  _ \ ___  ___ _   _| | |_
    | |_) / _ \/ __| | | | | __|
    |  _ <  __/\__ \ |_| | | |_
    |_| \_\___||___/\__,_|_|\__|
    Elegant error handling in C
])


# Check if the source folder is correct
AC_CONFIG_SRCDIR([src/result.h])


# Checks for programs.
AC_PROG_CC
AC_PROG_CPP


# Checks for header files.
AC_CHECK_HEADERS([stdbool.h])


# Checks for compiler characteristics
AC_LANG([C])


# The config file is generated but not used by the source code
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    result.pc
    Makefile
])


# Automake initialisation
AM_INIT_AUTOMAKE([
    -Wall
    -Werror
    foreign
    subdir-objects
    no-define
])


AC_OUTPUT
