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

RESULT_STRUCT(int, char);

/**
 * Tests `RESULT_SUCCESS`.
 */
int main() {
    // Given
    const RESULT(int, char) result = RESULT_SUCCESS(512);
    // Then
    TEST_ASSERT_FALSE(result._failed);
    TEST_ASSERT_INT_EQUALS(result._value._success, 512);
#ifndef NDEBUG
    TEST_ASSERT_STR_EQUALS(result._debug._func, "main");
    TEST_ASSERT_STR_CONTAINS(result._debug._file, "result_success.c");
    TEST_ASSERT_INT_EQUALS(result._debug._line, 27);
#endif
    TEST_PASS;
}
