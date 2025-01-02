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

typedef struct { int x;	int y; } point;
typedef const char * text;
RESULT_STRUCT(point, text);
RESULT_STRUCT(int, char);

#define POINT(x, y) \
    ((point) { x, y })

static RESULT(int, char) validate(const point p) {
    return p.x == 0 && p.y == 0 ? (RESULT(int, char)) RESULT_FAILURE('?') : (RESULT(int, char)) RESULT_SUCCESS(p.x + p.y);
}

static RESULT(int, char) first_char(const char * s) {
    return *s == 'S' ? (RESULT(int, char)) RESULT_SUCCESS(1) : (RESULT(int, char)) RESULT_FAILURE(*s);
}

/**
 * Tests `RESULT_FLAT_MAP` using functions.
 */
int main() {
    // Given
    const RESULT(point, text) success1 = RESULT_SUCCESS(POINT(123, 456));
    const RESULT(point, text) success2 = RESULT_SUCCESS(POINT(0, 0));
    const RESULT(point, text) failure1 = RESULT_FAILURE("Small mistake");
    const RESULT(point, text) failure2 = RESULT_FAILURE("Failure");
    // When
	const RESULT(int, char) mapped_success1 = RESULT_FLAT_MAP(success1, validate, first_char);
	const RESULT(int, char) mapped_success2 = RESULT_FLAT_MAP(success2, validate, first_char);
	const RESULT(int, char) mapped_failure1 = RESULT_FLAT_MAP(failure1, validate, first_char);
	const RESULT(int, char) mapped_failure2 = RESULT_FLAT_MAP(failure2, validate, first_char);
	// Then
	TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_success1));
	TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_success1), 579);
	TEST_ASSERT(RESULT_HAS_FAILURE(mapped_success2));
	TEST_ASSERT_CHAR_EQUALS(RESULT_USE_SUCCESS(mapped_success2), '?');
	TEST_ASSERT(RESULT_HAS_SUCCESS(mapped_failure1));
	TEST_ASSERT_INT_EQUALS(RESULT_USE_SUCCESS(mapped_failure1), 1);
	TEST_ASSERT(RESULT_HAS_FAILURE(mapped_failure2));
	TEST_ASSERT_CHAR_EQUALS(RESULT_USE_FAILURE(mapped_failure2), 'F');
    TEST_PASS;
}
