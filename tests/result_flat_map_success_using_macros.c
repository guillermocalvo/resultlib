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

typedef struct { int x; int y; } point;
typedef const char * text;
RESULT_STRUCT(int, text);
RESULT_STRUCT(point, text);

#define POINT(x, y) \
    ((point) { x, y })

#define validate(p) \
    p.x == 0 && p.y == 0 ? (RESULT(int, text)) RESULT_FAILURE("Invalid point") : (RESULT(int, text)) RESULT_SUCCESS(p.x + p.y)

/**
 * Tests `RESULT_FLAT_MAP_SUCCESS` using macros.
 */
int main() {
    // Given
    const RESULT(point, text) success1 = RESULT_SUCCESS(POINT(123, 456));
    const RESULT(point, text) success2 = RESULT_SUCCESS(POINT(0, 0));
    const RESULT(point, text) failure1 = RESULT_FAILURE("Failure");
    // When
    const RESULT(int, text) mapped_success1 = RESULT_FLAT_MAP_SUCCESS(success1, validate);
    const RESULT(int, text) mapped_success2 = RESULT_FLAT_MAP_SUCCESS(success2, validate);
    const RESULT(int, text) mapped_failure1 = RESULT_FLAT_MAP_SUCCESS(failure1, validate);
    // Then
    TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_success1));
    TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_success1), 579);
    TEST_ASSERT(RESULT_HAS_FAILURE(mapped_success2));
    TEST_ASSERT_STR_EQUALS(RESULT_USE_FAILURE(mapped_success2), "Invalid point");
    TEST_ASSERT(RESULT_HAS_FAILURE(mapped_failure1));
    TEST_ASSERT_STR_EQUALS(RESULT_USE_FAILURE(mapped_failure1), "Failure");
    TEST_PASS;
}
