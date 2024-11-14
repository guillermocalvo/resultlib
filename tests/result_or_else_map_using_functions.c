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
RESULT_STRUCT(int, text);

static int to_number(const char * s) {
    return *s == 'E' ? 1 : -1;
}

/**
 * Tests `RESULT_OR_ELSE_MAP` using functions.
 */
int main() {
    // Given
    const RESULT(int, text) success1 = RESULT_SUCCESS(512);
    const RESULT(int, text) failure1 = RESULT_FAILURE("Failure");
    const RESULT(int, text) failure2 = RESULT_FAILURE("Error");
    // When
    const int success1_or_else_map = RESULT_OR_ELSE_MAP(success1, to_number);
    const int failure1_or_else_map = RESULT_OR_ELSE_MAP(failure1, to_number);
    const int failure2_or_else_map = RESULT_OR_ELSE_MAP(failure2, to_number);
    // Then
    TEST_ASSERT_INT_EQUALS(success1_or_else_map, 512);
    TEST_ASSERT_INT_EQUALS(failure1_or_else_map, -1);
    TEST_ASSERT_INT_EQUALS(failure2_or_else_map, 1);
    TEST_PASS;
}
