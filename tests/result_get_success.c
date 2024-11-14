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

#include <stddef.h>
#include <result.h>
#include "test.h"

typedef const char * text;
RESULT_STRUCT(int, text);

/**
 * Tests `RESULT_GET_SUCCESS`.
 */
int main() {
    // Given
    const RESULT(int, text) success = RESULT_SUCCESS(512);
    const RESULT(int, text) failure = RESULT_FAILURE("Failure");
    // When
    const int *success_get_success = RESULT_GET_SUCCESS(success);
    const int *failure_get_success = RESULT_GET_SUCCESS(failure);
    // Then
    TEST_ASSERT_NOT_NULL(success_get_success);
    TEST_ASSERT_NULL(failure_get_success);
    TEST_ASSERT_INT_EQUALS(*success_get_success, 512);
    TEST_PASS;
}
