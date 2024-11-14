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

RESULT_STRUCT(int, char);

/**
 * Tests `RESULT_GET_FAILURE`.
 */
int main() {
    // Given
    const RESULT(int, char) success = RESULT_SUCCESS(512);
    const RESULT(int, char) failure = RESULT_FAILURE('A');
    // When
    const char * success_get_failure = RESULT_GET_FAILURE(success);
    const char * failure_get_failure = RESULT_GET_FAILURE(failure);
    // Then
    TEST_ASSERT_NULL(success_get_failure);
    TEST_ASSERT_NOT_NULL(failure_get_failure);
    TEST_ASSERT_CHAR_EQUALS(*failure_get_failure, 'A');
    TEST_PASS;
}
