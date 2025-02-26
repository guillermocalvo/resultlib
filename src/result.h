/*
 * Copyright 2025 Guillermo Calvo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * A header-only C library to handle errors elegantly.
 *
 * <a href="https://result.guillermo.dev/">
 * <img src="result-logo.svg">
 * </a>
 *
 * This library consists of one header file only. All you need to do is copy
 * `result.h` into your project, and include it.
 *
 * ```c
 * #include <result.h>
 * ```
 *
 * Since it's a header-only library, there is no library code to link against.
 *
 * @file        result.h
 * @version     0.1.0
 * @author      [Guillermo Calvo]
 * @copyright   Licensed under [Apache 2.0]
 * @see         For more information, visit the [project on GitHub]
 *
 * [Guillermo Calvo]: https://guillermo.dev
 * [Apache 2.0]: http://www.apache.org/licenses/LICENSE-2.0
 * [project on GitHub]: https://github.com/guillermocalvo/resultlib
 */

#ifndef RESULT_VERSION

/**
 * Returns the major version number of this library.
 */
#define RESULT_VERSION 0

#include <stddef.h> /* NULL */

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

/**
 * Returns the type specifier for results with the supplied success and failure
 * type names.
 *
 * For example, a result that can hold either an @p int success value or a
 * @p char failure value, has a type specifier:
 * <tt>struct result_of_int_and_char</tt>.
 *
 * @note
 * The struct tag will be generated via #RESULT_TAG.
 *
 * @remark
 * This macro is useful to define a variable of that specific type of results.
 *
 * @b Example:
 * @snippet example.c result
 *
 * @param success_type_name The success type name.
 * @param failure_type_name The failure type name.
 * @return The result type specifier.
 *
 * @see RESULT_STRUCT
 */
#define RESULT(success_type_name, failure_type_name)                        \
  struct RESULT_TAG(success_type_name, failure_type_name)

/**
 * Declares a result struct with a default tag and the supplied success and
 * failure types.
 *
 * @note
 * The struct tag will be generated via #RESULT_TAG.
 *
 * @remark
 * This macro is useful to declare result structs with a default tag.
 *
 * @b Example:
 * @snippet example.c result_struct
 *
 * @param success_type The success type.
 * @param failure_type The failure type.
 * @return The type definition.
 *
 * @see RESULT
 */
#define RESULT_STRUCT(success_type, failure_type)                           \
  RESULT_STRUCT_TAG(                                                        \
    success_type,                                                           \
    failure_type,                                                           \
    RESULT_TAG(success_type, failure_type)                                  \
  )

#ifndef NDEBUG

/**
 * Initializes a new successful result containing the supplied value.
 *
 * @b Example:
 * @snippet example.c result_success
 *
 * @param success The success value.
 * @return The initializer for a successful result holding @b success.
 *
 * @see RESULT_FAILURE
 */
#define RESULT_SUCCESS(success)                                             \
  {                                                                         \
    ._failed = false,                                                       \
    ._value = {                                                             \
      ._success = (success)                                                 \
    },                                                                      \
    ._debug = {                                                             \
      ._func = __func__,                                                    \
      ._file = __FILE__,                                                    \
      ._line = __LINE__                                                     \
    }                                                                       \
  }

#else

/**
 * Initializes a new successful result containing the supplied value.
 *
 * @b Example:
 * @snippet example.c result_success
 *
 * @param success The success value.
 * @return The initializer for a successful result holding @b success.
 *
 * @see RESULT_FAILURE
 */
#define RESULT_SUCCESS(success)                                             \
  {                                                                         \
    ._failed = false,                                                       \
    ._value = {                                                             \
      ._success = (success)                                                 \
    }                                                                       \
  }

#endif

#ifndef NDEBUG

/**
 * Initializes a new failed result containing the supplied value.
 *
 * @b Example:
 * @snippet example.c result_failure
 *
 * @param failure The failure value.
 * @return The initializer for a failed result holding @b failure.
 *
 * @see RESULT_SUCCESS
 */
#define RESULT_FAILURE(failure)                                             \
{                                                                           \
  ._failed = true,                                                          \
  ._value = {                                                               \
    ._failure = (failure)                                                   \
  },                                                                        \
  ._debug = {                                                               \
    ._func = __func__,                                                      \
    ._file = __FILE__,                                                      \
    ._line = __LINE__                                                       \
  }                                                                         \
}

#else

/**
 * Initializes a new failed result containing the supplied value.
 *
 * @b Example:
 * @snippet example.c result_failure
 *
 * @param failure The failure value.
 * @return The initializer for a failed result holding @b failure.
 *
 * @see RESULT_SUCCESS
 */
#define RESULT_FAILURE(failure)                                             \
  {                                                                         \
    ._failed = true,                                                        \
    ._value = {                                                             \
      ._failure = (failure)                                                 \
    }                                                                       \
  }

#endif

/**
 * Checks if a result contains a success value.
 *
 * @b Example:
 * @snippet example.c result_has_success
 *
 * @param result The result to check for success.
 * @return @p true if @b result is successful; otherwise @p false.
 *
 * @see RESULT_HAS_FAILURE
 */
#define RESULT_HAS_SUCCESS(result)                                          \
  (!(result)._failed)

/**
 * Checks if a result contains a failure value.
 *
 * @b Example:
 * @snippet example.c result_has_failure
 *
 * @param result The result to check for failure.
 * @return @p true if @b result is failed; otherwise @p false.
 *
 * @see RESULT_HAS_SUCCESS
 */
#define RESULT_HAS_FAILURE(result)                                          \
  ((result)._failed)

/**
 * Returns a result's success value.
 *
 * @pre @b result MUST be successful.
 *
 * @warning
 * If @b result is failed, the appropriate part of the object representation of
 * the failure value is reinterpreted as a success value (a process sometimes
 * called "type punning"), which may be a trap representation.
 *
 * @b Example:
 * @snippet example.c result_use_success
 *
 * @param result The result to retrieve the success value from.
 * @return @b result's success value.
 *
 * @see RESULT_USE_FAILURE
 */
#define RESULT_USE_SUCCESS(result)                                          \
  ((result)._value._success)

/**
 * Returns a result's failure value.
 *
 * @pre @b result MUST be failed.
 *
 * @warning
 * If @b result is successful, the appropriate part of the object representation
 * of the success value is reinterpreted as a failure value (a process sometimes
 * called "type punning"), which may be a trap representation.
 *
 * @b Example:
 * @snippet example.c result_use_failure
 *
 * @param result The result to retrieve the failure value from.
 * @return @b result's failure value.
 *
 * @see RESULT_USE_FAILURE
 */
#define RESULT_USE_FAILURE(result)                                          \
  ((result)._value._failure)

/**
 * Returns a result's success value as a possibly-null pointer.
 *
 * @pre @b result MUST be an @e value.
 *
 * @b Example:
 * @snippet example.c result_get_success
 *
 * @param result The result to retrieve the success value from.
 * @return A pointer to @b result's success value if successful; otherwise
 *   @p NULL.
 *
 * @see RESULT_GET_FAILURE
 */
#define RESULT_GET_SUCCESS(result)                                          \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? NULL                                                                  \
    : &RESULT_USE_SUCCESS(result)                                           \
  )

/**
 * Returns a result's failure value as a possibly-null pointer.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_get_failure
 *
 * @param result The result to retrieve the failure value from.
 * @return A pointer to @b result's failure value if failed; otherwise @p NULL.
 *
 * @see RESULT_GET_SUCCESS
 */
#define RESULT_GET_FAILURE(result)                                          \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? &RESULT_USE_FAILURE(result)                                           \
    : NULL                                                                  \
  )

/**
 * Returns a result's success value, or the supplied one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_or_else
 *
 * @param result The result to retrieve the success value from.
 * @param other The alternative success value.
 * @return @b result's success value if successful; otherwise @b other.
 *
 * @see RESULT_OR_ELSE_MAP
 */
#define RESULT_OR_ELSE(result, other)                                       \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (other)                                                               \
    : RESULT_USE_SUCCESS(result)                                            \
  )

/**
 * Returns a result's success value, or maps its failure value.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_or_else_map
 *
 * @param result The result to retrieve the success value from.
 * @param failure_mapper The mapping function or macro that produces the
 *   alternative success value.
 * @return @b result's success value if successful; otherwise the value produced
 *   by @b failure_mapper.
 *
 * @see RESULT_OR_ELSE
 */
#define RESULT_OR_ELSE_MAP(result, failure_mapper)                          \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (failure_mapper(RESULT_USE_FAILURE(result)))                          \
    : RESULT_USE_SUCCESS(result)                                            \
  )

/**
 * Performs the supplied action with a successful result's value.
 *
 * @b Example:
 * @snippet example.c result_if_success
 *
 * @param result The result whose success value will be used.
 * @param action The function or macro to be applied to @b result's success
 *   value.
 *
 * @see RESULT_IF_FAILURE
 * @see RESULT_IF_SUCCESS_OR_ELSE
 */
#define RESULT_IF_SUCCESS(result, action)                                   \
  do {                                                                      \
    typeof(result) _result = (result);                                      \
    if (RESULT_HAS_SUCCESS(_result)) {                                      \
      (void) (action(RESULT_USE_SUCCESS(_result)));                         \
    }                                                                       \
  } while(false)

/**
 * Performs the supplied action with a failed result's value.
 *
 * @b Example:
 * @snippet example.c result_if_failure
 *
 * @param result The result whose failure value will be used.
 * @param action The function or macro to be applied to @b result's failure
 *   value.
 *
 * @see RESULT_IF_SUCCESS
 * @see RESULT_IF_SUCCESS_OR_ELSE
 */
#define RESULT_IF_FAILURE(result, action)                                   \
  do {                                                                      \
    typeof(result) _result = (result);                                      \
    if (RESULT_HAS_FAILURE(_result)) {                                      \
      (void) (action(RESULT_USE_FAILURE(_result)));                         \
    }                                                                       \
  } while(false)

/**
 * Performs either of the supplied actions with a result's value.
 *
 * @b Example:
 * @snippet example.c result_if_success_or_else
 *
 * @param result The result whose value will be used.
 * @param success_action The function or macro to be applied to @b result's
 *   success value.
 * @param failure_action The function or macro to be applied to @b result's
 *   failure value.
 *
 * @see RESULT_IF_SUCCESS
 * @see RESULT_IF_FAILURE
 */
#define RESULT_IF_SUCCESS_OR_ELSE(result, success_action, failure_action)   \
  do {                                                                      \
    typeof(result) _result = (result);                                      \
    if (RESULT_HAS_FAILURE(_result)) {                                      \
      (void) (failure_action(RESULT_USE_FAILURE(_result)));                 \
    } else {                                                                \
      (void) (success_action(RESULT_USE_SUCCESS(_result)));                 \
    }                                                                       \
  } while(false)

/**
 * Conditionally transforms a successful result into a failed one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_filter
 *
 * @param result The result to map the success value from.
 * @param is_acceptable The predicate function or macro to apply to the
 *   success value.
 * @param failure The failure value if not acceptable.
 * @return If @b result is successful and its success value is deemed not
 *   acceptable, a new failed result holding @b failure; otherwise, the supplied
 *   @b result.
 *
 * @see RESULT_FILTER_MAP
 */
#define RESULT_FILTER(result, is_acceptable, failure)                       \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
            || (is_acceptable(RESULT_USE_SUCCESS(result)))                  \
    ? (result)                                                              \
    : (typeof(result)) RESULT_FAILURE(failure)                              \
  )

/**
 * Conditionally transforms a successful result into a failed one, mapping its
 * success value.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_filter_map
 *
 * @param result The result to map the success value from.
 * @param is_acceptable The predicate function or macro to apply to the
 *   success value.
 * @param success_mapper The mapping function or macro that produces the
 *   failure value.
 * @return If @b result is successful and its value is deemed not acceptable, a
 *   new failed result holding the value produced by @b success_mapper;
 *   otherwise, the supplied @b result.
 *
 * @see RESULT_FILTER
 */
#define RESULT_FILTER_MAP(result, is_acceptable, success_mapper)            \
  RESULT_FILTER(                                                            \
    result,                                                                 \
    is_acceptable,                                                          \
    (success_mapper(RESULT_USE_SUCCESS(result)))                            \
  )

/**
 * Conditionally transforms a failed result into a successful one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_recover
 *
 * @param result The result to map the failure value from.
 * @param is_recoverable The predicate function or macro to apply to the
 *   failure value.
 * @param success The success value if recoverable.
 * @return If @b result is failed and its value is deemed recoverable, a new
 *   successful result holding @b success; otherwise, the supplied @b result.
 *
 * @see RESULT_RECOVER_MAP
 */
#define RESULT_RECOVER(result, is_recoverable, success)                     \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
            && (is_recoverable(RESULT_USE_FAILURE(result)))                 \
    ? (typeof(result)) RESULT_SUCCESS(success)                              \
    : (result)                                                              \
  )

/**
 * Conditionally transforms a failed result into a successful one, mapping its
 * failure value.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_recover_map
 *
 * @param result The result to map the failure value from.
 * @param is_recoverable The predicate function or macro to apply to the
 *   failure value.
 * @param failure_mapper The mapping function or macro that produces the
 *   success value.
 * @return If @b result is failed and its value is deemed recoverable, a new
 *   successful result holding the value produced by @b failure_mapper;
 *   otherwise, the supplied @b result.
 *
 * @see RESULT_RECOVER
 */
#define RESULT_RECOVER_MAP(result, is_recoverable, failure_mapper)          \
  RESULT_RECOVER(                                                           \
    result,                                                                 \
    is_recoverable,                                                         \
    (failure_mapper(RESULT_USE_FAILURE(result)))                            \
  )

/**
 * Transforms the value of a successful result.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_map_success
 *
 * @param result The result whose success value will be transformed.
 * @param success_mapper The mapping function or macro that produces the new
 *   success value.
 * @param result_type The type of transformed result type.
 * @return If @b result is successful, a new successful result holding the value
 *   produced by @b success_mapper; otherwise, the supplied @b result.
 *
 * @see RESULT_MAP_FAILURE
 * @see RESULT_MAP
 */
#define RESULT_MAP_SUCCESS(result, success_mapper, result_type)             \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (result_type)                                                         \
      RESULT_FAILURE(RESULT_USE_FAILURE(result))                            \
    : (result_type)                                                         \
      RESULT_SUCCESS(success_mapper(RESULT_USE_SUCCESS(result)))            \
  )

/**
 * Transforms the value of a failed result.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_map_failure
 *
 * @param result The result whose failure value will be transformed.
 * @param failure_mapper The mapping function or macro that produces the new
 *   failure value.
 * @param result_type The type of transformed result type.
 * @return If @b result is failed, a new failed result holding the value
 *   produced by @b failure_mapper; otherwise, the supplied @b result.
 *
 * @see RESULT_MAP_SUCCESS
 * @see RESULT_MAP
 */
#define RESULT_MAP_FAILURE(result, failure_mapper, result_type)             \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (result_type)                                                         \
      RESULT_FAILURE(failure_mapper(RESULT_USE_FAILURE(result)))            \
    : (result_type)                                                         \
      RESULT_SUCCESS(RESULT_USE_SUCCESS(result))                            \
  )

/**
 * Transforms either the success or the failure value of a result.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_map
 *
 * @param result The result whose value will be transformed.
 * @param success_mapper The mapping function or macro that produces the new
 *   success value.
 * @param failure_mapper The mapping function or macro that produces the new
 *   failure value.
 * @param result_type The type of transformed result type.
 * @return If @b result is successful, a new successful result holding the value
 *   produced by @b success_mapper; otherwise, a new failed result holding the
 *   value produced by @b failure_mapper.
 *
 * @see RESULT_MAP_SUCCESS
 * @see RESULT_MAP_FAILURE
 */
#define RESULT_MAP(result, success_mapper, failure_mapper, result_type)     \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (result_type)                                                         \
      RESULT_FAILURE(failure_mapper(RESULT_USE_FAILURE(result)))            \
    : (result_type)                                                         \
      RESULT_SUCCESS(success_mapper(RESULT_USE_SUCCESS(result)))            \
  )

/**
 * Transforms a successful result into a different one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_flat_map_success
 *
 * @param result The result that will be transformed.
 * @param success_mapper The mapping function or macro that produces the new
 *   result if the given result is successful.
 * @return If @b result is successful, a new result produced by
 *   @b success_mapper; otherwise, the supplied @b result.
 *
 * @see RESULT_FLAT_MAP_FAILURE
 * @see RESULT_FLAT_MAP
 */
#define RESULT_FLAT_MAP_SUCCESS(result, success_mapper)                     \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (typeof(success_mapper(RESULT_USE_SUCCESS(result))))                  \
      RESULT_FAILURE(RESULT_USE_FAILURE(result))                            \
    : (success_mapper(RESULT_USE_SUCCESS(result)))                          \
  )

/**
 * Transforms a failed result into a different one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_flat_map_failure
 *
 * @param result The result that will be transformed.
 * @param failure_mapper The mapping function or macro that produces the new
 *   result if the given result is failed.
 * @return If @b result is failed, a new result produced by @b failure_mapper;
 *   otherwise, the supplied @b result.
 *
 * @see RESULT_FLAT_MAP_SUCCESS
 * @see RESULT_FLAT_MAP
 */
#define RESULT_FLAT_MAP_FAILURE(result, failure_mapper)                     \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (failure_mapper(RESULT_USE_FAILURE(result)))                          \
    : (typeof(failure_mapper(RESULT_USE_FAILURE(result))))                  \
      RESULT_SUCCESS(RESULT_USE_SUCCESS(result))                            \
  )

/**
 * Transforms a result into a different one.
 *
 * @pre @b result MUST be an @e lvalue.
 *
 * @b Example:
 * @snippet example.c result_flat_map
 *
 * @param result The result that will be transformed.
 * @param success_mapper The mapping function or macro that produces the new
 *   result if the given result is successful.
 * @param failure_mapper The mapping function or macro that produces the new
 *   result if the given result is failed.
 * @return The result produced by either @b success_mapper or @b failure_mapper.
 *
 * @see RESULT_FLAT_MAP_SUCCESS
 * @see RESULT_FLAT_MAP_FAILURE
 */
#define RESULT_FLAT_MAP(result, success_mapper, failure_mapper)             \
  (                                                                         \
    (void) &(result),                                                       \
    RESULT_HAS_FAILURE(result)                                              \
    ? (failure_mapper(RESULT_USE_FAILURE(result)))                          \
    : (success_mapper(RESULT_USE_SUCCESS(result)))                          \
  )

#ifndef NDEBUG

/**
 * Returns the function name where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The function name where @b result was created if @p NDEBUG is
 *   undefined; otherwise @p NULL.
 *
 * @see RESULT_DEBUG_FILE
 * @see RESULT_DEBUG_LINE
 */
#define RESULT_DEBUG_FUNC(result)                                           \
  ((result)._debug._func)

#else

/**
 * Returns the function name where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The function name where @b result was created if @p NDEBUG is
 *   undefined; otherwise @p NULL.
 *
 * @see RESULT_DEBUG_FILE
 * @see RESULT_DEBUG_LINE
 */
#define RESULT_DEBUG_FUNC(result)                                           \
  (NULL)

#endif

#ifndef NDEBUG

/**
 * Returns the source file name where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The source file name where @b result was created if @p NDEBUG is
 *   undefined; otherwise @p NULL.
 *
 * @see RESULT_DEBUG_FUNC
 * @see RESULT_DEBUG_LINE
 */
#define RESULT_DEBUG_FILE(result)                                           \
  ((result)._debug._file)

#else

/**
 * Returns the source file name where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The source file name where @b result was created if @p NDEBUG is
 *   undefined; otherwise @p NULL.
 *
 * @see RESULT_DEBUG_FUNC
 * @see RESULT_DEBUG_LINE
 */
#define RESULT_DEBUG_FILE(result)                                           \
  (NULL)

#endif

#ifndef NDEBUG

/**
 * Returns the source line number where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The source line number where @ result was created if @p NDEBUG is
 *   undefined; otherwise zero.
 *
 * @see RESULT_DEBUG_FUNC
 * @see RESULT_DEBUG_FILE
 */
#define RESULT_DEBUG_LINE(result)                                           \
  ((result)._debug._line)

#else

/**
 * Returns the source line number where a result was created.
 *
 * @b Example:
 * @snippet example.c result_debug
 *
 * @param result The result to retrieve the debug information from.
 * @return The source line number where @ result was created if @p NDEBUG is
 *   undefined; otherwise zero.
 *
 * @see RESULT_DEBUG_FUNC
 * @see RESULT_DEBUG_FILE
 */
#define RESULT_DEBUG_LINE(result)                                           \
  (0)

#endif

/**
 * Returns the struct tag for results with the supplied success and failure
 * type names.
 *
 * For example, a result that can hold either an @p int success value or a
 * @p char failure value, has a struct tag: @p result_of_int_and_char.
 *
 * @b Example:
 * @snippet example.c result_tag
 *
 * @param success_type_name The success type name.
 * @param failure_type_name The failure type name.
 * @return The result struct tag.
 *
 * @see RESULT_STRUCT_TAG
 */
#define RESULT_TAG(success_type_name, failure_type_name)                    \
  result_of_ ## success_type_name ## _and_ ## failure_type_name

#ifndef NDEBUG

/**
 * Declares a result struct with the supplied success and failure types.
 *
 * @pre @b struct_tag SHOULD be generated via #RESULT_TAG.
 *
 * @warning
 * The exact sequence of members that make up a result struct MUST be considered
 * part of the implementation details. Results SHOULD only be created and
 * accessed using the macros provided in this header file.
 *
 * @remark
 * This macro is useful to declare result structs.
 *
 * @b Example:
 * @snippet example.c result_tag
 *
 * @param success_type The success type.
 * @param failure_type The failure type.
 * @param struct_tag The struct tag.
 * @return The struct declaration.
 *
 * @see RESULT_STRUCT
 * @see RESULT_TAG
 */
#define RESULT_STRUCT_TAG(success_type, failure_type, struct_tag)           \
  struct struct_tag {                                                       \
    bool _failed;                                                           \
    union {                                                                 \
      success_type _success;                                                \
      failure_type _failure;                                                \
    } _value;                                                               \
    struct {                                                                \
      const char * _func;                                                   \
      const char * _file;                                                   \
      int _line;                                                            \
    } _debug;                                                               \
  }

#else

/**
 * Declares a result struct with the supplied success and failure types.
 *
 * @pre @b struct_tag SHOULD be generated via #RESULT_TAG.
 *
 * @warning
 * The exact sequence of members that make up a result struct MUST be considered
 * part of the implementation details. Results SHOULD only be created and
 * accessed using the macros provided in this header file.
 *
 * @remark
 * This macro is useful to declare result structs.
 *
 * @b Example:
 * @snippet example.c result_tag
 *
 * @param success_type The success type.
 * @param failure_type The failure type.
 * @param struct_tag The struct tag.
 * @return The struct declaration.
 *
 * @see RESULT_STRUCT
 * @see RESULT_TAG
 */
#define RESULT_STRUCT_TAG(success_type, failure_type, struct_tag)           \
  struct struct_tag {                                                       \
    bool _failed;                                                           \
    union {                                                                 \
      success_type _success;                                                \
      failure_type _failure;                                                \
    } _value;                                                               \
  }

#endif

#endif
