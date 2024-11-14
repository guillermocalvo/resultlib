cmake_minimum_required(VERSION 3.29)

project(resultlib C)

set(CMAKE_C_STANDARD 23)

enable_testing()

set(TESTS
        result_success
        result_failure
        result_has_success
        result_has_failure
        result_use_success
        result_use_failure
        result_get_success
        result_get_failure
        result_or_else
        result_or_else_map_using_functions
        result_or_else_map_using_macros
        result_if_success_using_functions
        result_if_success_using_macros
        result_if_failure_using_functions
        result_if_failure_using_macros
        result_if_success_or_else_using_functions
        result_if_success_or_else_using_macros
        result_filter_using_functions
        result_filter_using_macros
        result_filter_map_using_functions
        result_filter_map_using_macros
        result_recover_using_macros
        result_recover_using_functions
        result_recover_map_using_macros
        result_recover_map_using_functions
        result_map_success_using_functions
        result_map_success_using_macros
        result_map_failure_using_functions
        result_map_failure_using_macros
        result_map_using_functions
        result_map_using_macros
        result_flat_map_success_using_functions
        result_flat_map_success_using_macros
        result_flat_map_failure_using_functions
        result_flat_map_failure_using_macros
        result_flat_map_using_functions
        result_flat_map_using_macros
        result_debug_func
        result_debug_file
        result_debug_line
)

foreach(TEST IN LISTS TESTS)
    add_executable(${TEST} "tests/${TEST}.c")
    set_target_properties(${TEST} PROPERTIES COMPILE_WARNING_AS_ERROR ON)
    target_include_directories(${TEST} PUBLIC src)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}>)
    set_property(TEST ${TEST} PROPERTY SKIP_RETURN_CODE 77)
endforeach()
