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

#include <result.h>
#include "test.h"

typedef const char *text;

RESULT_STRUCT(int, text);

#define is_within_range(x) \
    x >= 1 && x <= 10

/**
 * Tests `RESULT_FILTER` using macros.
 */
int main() {
    // Given
    const RESULT(int, text) success1 = RESULT_SUCCESS(5);
    const RESULT(int, text) success2 = RESULT_SUCCESS(-10);
    const RESULT(int, text) failure1 = RESULT_FAILURE("Failure");
    // When
    const RESULT(int, text) filtered_success1 = RESULT_FILTER(success1, is_within_range, "Out of range");
    const RESULT(int, text) filtered_success2 = RESULT_FILTER(success2, is_within_range, "Out of range");
    const RESULT(int, text) filtered_failure1 = RESULT_FILTER(failure1, is_within_range, "Out of range");
    // Then
    TEST_ASSERT(RESULT_HAS_SUCCESS(filtered_success1));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(filtered_success1), 5);
    TEST_ASSERT(RESULT_HAS_FAILURE(filtered_success2));
    TEST_ASSERT_STR_EQUALS(RESULT_USE_FAILURE(filtered_success2), "Out of range");
    TEST_ASSERT(RESULT_HAS_FAILURE(filtered_failure1));
    TEST_ASSERT_STR_EQUALS(RESULT_USE_FAILURE(filtered_failure1), "Failure");
    TEST_PASS;
}
