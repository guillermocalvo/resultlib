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

#define is_recoverable(s) \
    *s != 'F'

#define to_number(s) \
    *s == 'T' ? 1 : -1

/**
 * Tests `RESULT_RECOVER_MAP` using macros.
 */
int main() {
    // Given
    const RESULT(int, text) success1 = RESULT_SUCCESS(512);
    const RESULT(int, text) failure1 = RESULT_FAILURE("Failure");
    const RESULT(int, text) failure2 = RESULT_FAILURE("Try again");
    const RESULT(int, text) failure3 = RESULT_FAILURE("Empty result");
    // When
    const RESULT(int, text) recovered_success1 = RESULT_RECOVER_MAP(success1, is_recoverable, to_number);
    const RESULT(int, text) recovered_failure1 = RESULT_RECOVER_MAP(failure1, is_recoverable, to_number);
    const RESULT(int, text) recovered_failure2 = RESULT_RECOVER_MAP(failure2, is_recoverable, to_number);
    const RESULT(int, text) recovered_failure3 = RESULT_RECOVER_MAP(failure3, is_recoverable, to_number);
    // Then
    TEST_ASSERT(RESULT_HAS_SUCCESS(recovered_success1));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(recovered_success1), 512);
    TEST_ASSERT(RESULT_HAS_FAILURE(recovered_failure1));
    TEST_ASSERT_STR_EQUALS(RESULT_USE_FAILURE(recovered_failure1), "Failure");
    TEST_ASSERT(RESULT_HAS_SUCCESS(recovered_failure2));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(recovered_failure2), 1);
    TEST_ASSERT(RESULT_HAS_SUCCESS(recovered_failure3));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(recovered_failure3), -1);
    TEST_PASS;
}
