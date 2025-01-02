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

/**
 * Tests `RESULT_DEBUG_FUNC`.
 */
int main() {
#ifdef NDEBUG
    TEST_SKIP("NDEBUG is defined");
#else
    // Given
    RESULT_STRUCT(int, char);
    const RESULT(int, char) success = RESULT_SUCCESS(512);
    const RESULT(int, char) failure = RESULT_FAILURE('A');
    // Then
    TEST_ASSERT_STR_EQUALS(RESULT_DEBUG_FUNC(success), "main");
    TEST_ASSERT_STR_EQUALS(RESULT_DEBUG_FUNC(failure), "main");
    TEST_PASS;
#endif
}
