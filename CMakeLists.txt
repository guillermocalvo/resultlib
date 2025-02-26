cmake_minimum_required(VERSION 3.29)

project(resultlib C)

set(CMAKE_C_STANDARD 23)
set(RESULT_VERSION "1.0")

include(FetchContent)
FetchContent_Declare(
        doxygen-awesome-css
        URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(doxygen-awesome-css)
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

# Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
            COMMENT "Generating documentation with Doxygen"
            VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Install Doxygen to generate the documentation")
endif (DOXYGEN_FOUND)

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

add_executable(examples
        "examples/example.c"
        "examples/pet-store.c"
        "examples/application.c")
set_target_properties(examples PROPERTIES COMPILE_WARNING_AS_ERROR ON)
target_include_directories(examples PUBLIC src)
add_test(NAME examples COMMAND $<TARGET_FILE:examples>)
set_property(TEST examples PROPERTY SKIP_RETURN_CODE 77)
