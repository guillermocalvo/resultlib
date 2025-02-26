#
# Result Library
#
# Copyright (c) 2025 Guillermo Calvo
# Licensed under the Apache License, Version 2.0
#

AUTOMAKE_OPTIONS = foreign subdir-objects

AM_CFLAGS = -Wall -Werror --pedantic -Isrc

include_HEADERS = src/result.h

# Documentation

docsdir = $(datadir)/docs/result
docs_DATA = docs/*


# Check

check_PROGRAMS =                                        \
    bin/check/result_success                            \
    bin/check/result_failure                            \
    bin/check/result_has_success                        \
    bin/check/result_has_failure                        \
    bin/check/result_use_success                        \
    bin/check/result_use_failure                        \
    bin/check/result_get_success                        \
    bin/check/result_get_failure                        \
    bin/check/result_or_else                            \
    bin/check/result_or_else_map_using_functions        \
    bin/check/result_or_else_map_using_macros           \
    bin/check/result_if_success_using_functions         \
    bin/check/result_if_success_using_macros            \
    bin/check/result_if_failure_using_functions         \
    bin/check/result_if_failure_using_macros            \
    bin/check/result_if_success_or_else_using_functions \
    bin/check/result_if_success_or_else_using_macros    \
    bin/check/result_filter_using_functions             \
    bin/check/result_filter_using_macros                \
    bin/check/result_filter_map_using_functions         \
    bin/check/result_filter_map_using_macros            \
    bin/check/result_recover_using_macros               \
    bin/check/result_recover_using_functions            \
    bin/check/result_recover_map_using_macros           \
    bin/check/result_recover_map_using_functions        \
    bin/check/result_map_success_using_functions        \
    bin/check/result_map_success_using_macros           \
    bin/check/result_map_failure_using_functions        \
    bin/check/result_map_failure_using_macros           \
    bin/check/result_map_using_functions                \
    bin/check/result_map_using_macros                   \
    bin/check/result_flat_map_success_using_functions   \
    bin/check/result_flat_map_success_using_macros      \
    bin/check/result_flat_map_failure_using_functions   \
    bin/check/result_flat_map_failure_using_macros      \
    bin/check/result_flat_map_using_functions           \
    bin/check/result_flat_map_using_macros              \
    bin/check/result_debug_func                         \
    bin/check/result_debug_file                         \
    bin/check/result_debug_line                         \
    bin/check/examples

TESTS =                                                 \
    bin/check/result_success                            \
    bin/check/result_failure                            \
    bin/check/result_has_success                        \
    bin/check/result_has_failure                        \
    bin/check/result_use_success                        \
    bin/check/result_use_failure                        \
    bin/check/result_get_success                        \
    bin/check/result_get_failure                        \
    bin/check/result_or_else                            \
    bin/check/result_or_else_map_using_functions        \
    bin/check/result_or_else_map_using_macros           \
    bin/check/result_if_success_using_functions         \
    bin/check/result_if_success_using_macros            \
    bin/check/result_if_failure_using_functions         \
    bin/check/result_if_failure_using_macros            \
    bin/check/result_if_success_or_else_using_functions \
    bin/check/result_if_success_or_else_using_macros    \
    bin/check/result_filter_using_functions             \
    bin/check/result_filter_using_macros                \
    bin/check/result_filter_map_using_functions         \
    bin/check/result_filter_map_using_macros            \
    bin/check/result_recover_using_macros               \
    bin/check/result_recover_using_functions            \
    bin/check/result_recover_map_using_macros           \
    bin/check/result_recover_map_using_functions        \
    bin/check/result_map_success_using_functions        \
    bin/check/result_map_success_using_macros           \
    bin/check/result_map_failure_using_functions        \
    bin/check/result_map_failure_using_macros           \
    bin/check/result_map_using_functions                \
    bin/check/result_map_using_macros                   \
    bin/check/result_flat_map_success_using_functions   \
    bin/check/result_flat_map_success_using_macros      \
    bin/check/result_flat_map_failure_using_functions   \
    bin/check/result_flat_map_failure_using_macros      \
    bin/check/result_flat_map_using_functions           \
    bin/check/result_flat_map_using_macros              \
    bin/check/result_debug_func                         \
    bin/check/result_debug_file                         \
    bin/check/result_debug_line                         \
    bin/check/examples

tests: check


# Tests

bin_check_result_success_SOURCES                            = tests/result_success.c
bin_check_result_failure_SOURCES                            = tests/result_failure.c
bin_check_result_has_success_SOURCES                        = tests/result_has_success.c
bin_check_result_has_failure_SOURCES                        = tests/result_has_failure.c
bin_check_result_use_success_SOURCES                        = tests/result_use_success.c
bin_check_result_use_failure_SOURCES                        = tests/result_use_failure.c
bin_check_result_get_success_SOURCES                        = tests/result_get_success.c
bin_check_result_get_failure_SOURCES                        = tests/result_get_failure.c
bin_check_result_or_else_SOURCES                            = tests/result_or_else.c
bin_check_result_or_else_map_using_functions_SOURCES        = tests/result_or_else_map_using_functions.c
bin_check_result_or_else_map_using_macros_SOURCES           = tests/result_or_else_map_using_macros.c
bin_check_result_if_success_using_functions_SOURCES         = tests/result_if_success_using_functions.c
bin_check_result_if_success_using_macros_SOURCES            = tests/result_if_success_using_macros.c
bin_check_result_if_failure_using_functions_SOURCES         = tests/result_if_failure_using_functions.c
bin_check_result_if_failure_using_macros_SOURCES            = tests/result_if_failure_using_macros.c
bin_check_result_if_success_or_else_using_functions_SOURCES = tests/result_if_success_or_else_using_functions.c
bin_check_result_if_success_or_else_using_macros_SOURCES    = tests/result_if_success_or_else_using_macros.c
bin_check_result_filter_using_functions_SOURCES             = tests/result_filter_using_functions.c
bin_check_result_filter_using_macros_SOURCES                = tests/result_filter_using_macros.c
bin_check_result_filter_map_using_functions_SOURCES         = tests/result_filter_map_using_functions.c
bin_check_result_filter_map_using_macros_SOURCES            = tests/result_filter_map_using_macros.c
bin_check_result_recover_using_macros_SOURCES               = tests/result_recover_using_macros.c
bin_check_result_recover_using_functions_SOURCES            = tests/result_recover_using_functions.c
bin_check_result_recover_map_using_macros_SOURCES           = tests/result_recover_map_using_macros.c
bin_check_result_recover_map_using_functions_SOURCES        = tests/result_recover_map_using_functions.c
bin_check_result_map_success_using_functions_SOURCES        = tests/result_map_success_using_functions.c
bin_check_result_map_success_using_macros_SOURCES           = tests/result_map_success_using_macros.c
bin_check_result_map_failure_using_functions_SOURCES        = tests/result_map_failure_using_functions.c
bin_check_result_map_failure_using_macros_SOURCES           = tests/result_map_failure_using_macros.c
bin_check_result_map_using_functions_SOURCES                = tests/result_map_using_functions.c
bin_check_result_map_using_macros_SOURCES                   = tests/result_map_using_macros.c
bin_check_result_flat_map_success_using_functions_SOURCES   = tests/result_flat_map_success_using_functions.c
bin_check_result_flat_map_success_using_macros_SOURCES      = tests/result_flat_map_success_using_macros.c
bin_check_result_flat_map_failure_using_functions_SOURCES   = tests/result_flat_map_failure_using_functions.c
bin_check_result_flat_map_failure_using_macros_SOURCES      = tests/result_flat_map_failure_using_macros.c
bin_check_result_flat_map_using_functions_SOURCES           = tests/result_flat_map_using_functions.c
bin_check_result_flat_map_using_macros_SOURCES              = tests/result_flat_map_using_macros.c
bin_check_result_debug_func_SOURCES                         = tests/result_debug_func.c
bin_check_result_debug_file_SOURCES                         = tests/result_debug_file.c
bin_check_result_debug_line_SOURCES                         = tests/result_debug_line.c
bin_check_examples_SOURCES                                  = examples/example.c examples/pet-store.c examples/application.c


# Generate documentation

docs: docs/html/index.html

docs/html/index.html: docs/Doxyfile docs/doxygen-awesome.css docs/doxygen-awesome-sidebar-only.css
	doxygen docs/Doxyfile

docs/doxygen-awesome.css:
	wget --verbose --output-document docs/doxygen-awesome.css https://github.com/jothepro/doxygen-awesome-css/raw/refs/heads/main/doxygen-awesome.css

docs/doxygen-awesome-sidebar-only.css:
	wget --verbose --output-document docs/doxygen-awesome-sidebar-only.css https://github.com/jothepro/doxygen-awesome-css/raw/refs/heads/main/doxygen-awesome-sidebar-only.css
