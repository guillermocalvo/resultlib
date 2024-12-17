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
#include <string.h>
#include <assert.h>
#include <result.h>
#include "pet-store.h"

RESULT_STRUCT_TAG(Pet, const char *, RESULT_TAG(Pet, msg));
RESULT_STRUCT_TAG(pet_status, const char *, RESULT_TAG(pet_status, msg));

typedef int IMPLEMENTATION;

static struct pet default_pet = { .id = 100, .name = "Default pet", .status = AVAILABLE };
static int side_effect = 0;
static pet_error last_error = OK;

static const char * pet_error_message(pet_error code) {
    switch (code) {
        case OK: return "OK";
        case PET_NOT_FOUND: return "Pet not found";
        case PET_NOT_AVAILABLE: return "Pet not available";
        case PET_ALREADY_SOLD: return "Pet already sold";
        default: return "Unknown error";
    }
}

static RESULT(Pet, pet_error) pet_buy(Pet pet) {
    if (PET_STATUS(pet) != AVAILABLE) {
        return (RESULT(Pet, pet_error)) RESULT_FAILURE(PET_NOT_AVAILABLE);
    }
    PET_STATUS(pet) = SOLD;
    return (RESULT(Pet, pet_error)) RESULT_SUCCESS(pet);
}

static RESULT(Pet, pet_error) pet_get_default(pet_error code) {
    if (code == PET_NOT_FOUND) {
        return (RESULT(Pet, pet_error)) RESULT_SUCCESS(&default_pet);
    }
    return (RESULT(Pet, pet_error)) RESULT_FAILURE(code);
}

static void set_side_effect(int value) {
    side_effect = value;
}

static void log_error(pet_error error) {
    last_error = error;
}

/**
 * Example snippets.
 */
int main() {

#ifdef NDEBUG
    return 77;
#else

    {
//! [result_struct]
RESULT_STRUCT(pet_status, pet_error);
//! [result_struct]
    }

    {
//! [result]
RESULT(pet_status, pet_error) result;
//! [result]
    }

    {
//! [result_success]
RESULT(pet_status, pet_error) result = RESULT_SUCCESS(AVAILABLE);
//! [result_success]
    }

    {
//! [result_failure]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
//! [result_failure]
    }

    {
//! [result_has_success]
RESULT(pet_status, pet_error) result = RESULT_SUCCESS(AVAILABLE);
bool has_success = RESULT_HAS_SUCCESS(result);
assert(has_success == true);
//! [result_has_success]
    }

    {
//! [result_has_failure]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
bool has_failure = RESULT_HAS_FAILURE(result);
assert(has_failure == true);
//! [result_has_failure]
    }

    {
//! [result_use_success]
RESULT(pet_status, pet_error) result = RESULT_SUCCESS(AVAILABLE);
pet_status value = RESULT_USE_SUCCESS(result);
assert(value == AVAILABLE);
//! [result_use_success]
    }

    {
//! [result_use_failure]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
pet_error value = RESULT_USE_FAILURE(result);
assert(value == PET_NOT_FOUND);
//! [result_use_failure]
    }

    {
//! [result_get_success]
RESULT(pet_status, pet_error) result = RESULT_SUCCESS(AVAILABLE);
pet_status * value = RESULT_GET_SUCCESS(result);
assert(*value == AVAILABLE);
//! [result_get_success]
    }

    {
//! [result_get_failure]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
pet_error * value = RESULT_GET_FAILURE(result);
assert(*value == PET_NOT_FOUND);
//! [result_get_failure]
    }

    {
//! [result_or_else]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_ALREADY_SOLD);
pet_status value = RESULT_OR_ELSE(result, PENDING);
assert(value == PENDING);
//! [result_or_else]
    }

    {
//! [result_or_else_map]
#define ERROR_TO_STATUS(x) x == PET_ALREADY_SOLD ? SOLD : PENDING
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_ALREADY_SOLD);
pet_status value = RESULT_OR_ELSE_MAP(result, ERROR_TO_STATUS);
assert(value == SOLD);
//! [result_or_else_map]
    }
#undef ERROR_TO_STATUS

    {
RESULT_STRUCT(int, pet_error);
//! [result_if_success]
RESULT(int, pet_error) result = RESULT_SUCCESS(123);
side_effect = 0;
RESULT_IF_SUCCESS(result, set_side_effect);
assert(side_effect == 123);
//! [result_if_success]
    }

    {
RESULT_STRUCT(int, pet_error);
//! [result_if_failure]
RESULT(int, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
last_error = OK;
RESULT_IF_FAILURE(result, log_error);
assert(last_error == PET_NOT_FOUND);
//! [result_if_failure]
    }

    {
RESULT_STRUCT(int, pet_error);
//! [result_if_success_or_else]
RESULT(int, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
side_effect = 0;
last_error = OK;
RESULT_IF_SUCCESS_OR_ELSE(result, set_side_effect, log_error);
assert(side_effect == 0);
assert(last_error == PET_NOT_FOUND);
//! [result_if_success_or_else]
    }

#define is_available(pet) (PET_STATUS(pet) == AVAILABLE)

    {
//! [result_filter]
struct pet sold = { .status = SOLD };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&sold);
RESULT(Pet, pet_error) filtered = RESULT_FILTER(result, is_available, PET_NOT_AVAILABLE);
assert(RESULT_USE_FAILURE(filtered) == PET_NOT_AVAILABLE);
//! [result_filter]
    }

    {
//! [result_filter_map]
#define PET_TO_ERROR(pet) (PET_STATUS(pet) == SOLD ? PET_ALREADY_SOLD : PET_NOT_AVAILABLE)
struct pet sold = { .status = SOLD };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&sold);
RESULT(Pet, pet_error) filtered = RESULT_FILTER_MAP(result, is_available, PET_TO_ERROR);
assert(RESULT_USE_FAILURE(filtered) == PET_ALREADY_SOLD);
//! [result_filter_map]
    }

#undef is_available

#define is_not_available(x) (x == PET_ALREADY_SOLD || x == PET_NOT_AVAILABLE)

    {
//! [result_recover]
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_AVAILABLE);
RESULT(pet_status, pet_error) recovered = RESULT_RECOVER(result, is_not_available, SOLD);
assert(RESULT_USE_SUCCESS(recovered) == SOLD);
//! [result_recover]
    }

    {
//! [result_recover_map]
#define ERROR_TO_STATUS(x) x == PET_ALREADY_SOLD ? SOLD : PENDING
RESULT(pet_status, pet_error) result = RESULT_FAILURE(PET_NOT_AVAILABLE);
RESULT(pet_status, pet_error) recovered = RESULT_RECOVER_MAP(result, is_not_available, ERROR_TO_STATUS);
assert(RESULT_USE_SUCCESS(recovered) == PENDING);
//! [result_recover_map]
    }
#undef ERROR_TO_STATUS

#undef is_not_available

    {
//! [result_map_success]
struct pet sold = { .status = SOLD };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&sold);
RESULT(pet_status, pet_error) mapped = RESULT_MAP_SUCCESS(result, PET_STATUS, typeof(mapped));
assert(RESULT_USE_SUCCESS(mapped) == SOLD);
//! [result_map_success]
    }

    {
//! [result_map_failure]
RESULT(Pet, pet_error) result = RESULT_FAILURE(PET_NOT_AVAILABLE);
RESULT(Pet, msg) mapped = RESULT_MAP_FAILURE(result, pet_error_message, typeof(mapped));
assert(strcmp(RESULT_USE_FAILURE(mapped), "Pet not available") == 0);
//! [result_map_failure]
    }

    {
//! [result_map]
struct pet sold = { .status = SOLD };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&sold);
RESULT(pet_status, msg) mapped = RESULT_MAP(result, PET_STATUS, pet_error_message, typeof(mapped));
assert(RESULT_USE_SUCCESS(mapped) == SOLD);
//! [result_map]
    }

    {
//! [result_flat_map_success]
struct pet sold = { .status = SOLD };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&sold);
RESULT(Pet, pet_error) mapped = RESULT_FLAT_MAP_SUCCESS(result, pet_buy);
assert(RESULT_USE_FAILURE(mapped) == PET_NOT_AVAILABLE);
//! [result_flat_map_success]
    }

    {
//! [result_flat_map_failure]
RESULT(Pet, pet_error) result = RESULT_FAILURE(PET_NOT_FOUND);
RESULT(Pet, pet_error) mapped = RESULT_FLAT_MAP_FAILURE(result, pet_get_default);
assert(strcmp(PET_NAME(RESULT_USE_SUCCESS(mapped)), "Default pet") == 0);
//! [result_flat_map_failure]
    }

    {
//! [result_flat_map]
struct pet available = { .status = AVAILABLE };
RESULT(Pet, pet_error) result = RESULT_SUCCESS(&available);
RESULT(Pet, pet_error) mapped = RESULT_FLAT_MAP(result, pet_buy, pet_get_default);
assert(RESULT_USE_SUCCESS(mapped) == &available);
assert(PET_STATUS(RESULT_USE_SUCCESS(mapped)) == SOLD);
//! [result_flat_map]
    }

    return 0;
#endif
}
