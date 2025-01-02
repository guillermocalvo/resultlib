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
 * Tests `RESULT_USE_FAILURE`.
 */
int main() {
    // Given
    const RESULT(int, char) success = RESULT_SUCCESS(512);
    const RESULT(int, char) failure = RESULT_FAILURE('A');
    // Then
    TEST_ASSERT_CHAR_EQUALS(RESULT_USE_FAILURE(success), (char) 512); // unsafe type punning
    TEST_ASSERT_CHAR_EQUALS(RESULT_USE_FAILURE(failure), 'A');
    TEST_PASS;
}
