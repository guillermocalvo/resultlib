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

typedef const char * text;
RESULT_STRUCT(int, text);

static bool on_success1_executed = false;
static bool on_success2_executed = false;
static bool on_failure1_executed = false;
static bool on_failure2_executed = false;

#define on_success1(_) \
    on_success1_executed = true

#define on_success2(_) \
    on_success2_executed = true

#define on_failure1(_) \
    on_failure1_executed = true

#define on_failure2(_) \
    on_failure2_executed = true

/**
 * Tests `RESULT_IF_SUCCESS_OR_ELSE` using macros.
 */
int main() {
    // Given
    const RESULT(int, text) success = RESULT_SUCCESS(512);
    const RESULT(int, text) failure = RESULT_FAILURE("Failure");
    // When
    RESULT_IF_SUCCESS_OR_ELSE(success, on_success1, on_failure1);
    RESULT_IF_SUCCESS_OR_ELSE(failure, on_success2, on_failure2);
    // Then
    TEST_ASSERT_TRUE(on_success1_executed);
    TEST_ASSERT_FALSE(on_success2_executed);
    TEST_ASSERT_FALSE(on_failure1_executed);
    TEST_ASSERT_TRUE(on_failure2_executed);
    TEST_PASS;
}
