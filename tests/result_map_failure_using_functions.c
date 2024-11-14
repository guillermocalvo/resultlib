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

static char first_char(const char * s) {
    return *s;
}

/**
 * Tests `RESULT_MAP_FAILURE` using functions.
 */
int main() {
    // Given
    const RESULT(int, text) success = RESULT_SUCCESS(512);
    const RESULT(int, text) failure = RESULT_FAILURE("Failure");
    // When
    const RESULT(int, char) mapped_success = RESULT_MAP_FAILURE(success, first_char, RESULT(int, char));
    const RESULT(int, char) mapped_failure = RESULT_MAP_FAILURE(failure, first_char, RESULT(int, char));
    // Then
    TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_success));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_success), 512);
    TEST_ASSERT(RESULT_HAS_FAILURE(mapped_failure));
    TEST_ASSERT_CHAR_EQUALS(RESULT_USE_FAILURE(mapped_failure), 'F');
    TEST_PASS;
}