/*
 * Copyright 2024 Guillermo Calvo
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

typedef const char * text;
RESULT_STRUCT(int, char);
RESULT_STRUCT(int, text);

#define first_char(s) \
    *s == 'S' ? (RESULT(int, char)) RESULT_SUCCESS(1) : (RESULT(int, char)) RESULT_FAILURE(*s)

/**
 * Tests `RESULT_FLAT_MAP_FAILURE` using macros.
 */
int main() {
    // Given
    const RESULT(int, text) success1 = RESULT_SUCCESS(512);
    const RESULT(int, text) failure1 = RESULT_FAILURE("Big mistake");
    const RESULT(int, text) failure2 = RESULT_FAILURE("Small mistake");
    // When
    const RESULT(int, char) mapped_success1 = RESULT_FLAT_MAP_FAILURE(success1, first_char);
    const RESULT(int, char) mapped_failure1 = RESULT_FLAT_MAP_FAILURE(failure1, first_char);
    const RESULT(int, char) mapped_failure2 = RESULT_FLAT_MAP_FAILURE(failure2, first_char);
    // Then
    TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_success1));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_success1), 512);
    TEST_ASSERT(RESULT_HAS_FAILURE(mapped_failure1));
    TEST_ASSERT_CHAR_EQUALS(RESULT_USE_FAILURE(mapped_failure1), 'B');
    TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_failure2));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_failure2), 1);
    TEST_PASS;
}
