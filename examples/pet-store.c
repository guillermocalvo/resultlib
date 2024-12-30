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

//! [source]
#include <stddef.h>
#include "pet-store.h"

//! [array]
// Available pets in the store
static struct pet pets[] = {
  { .id = 0, .name = "Rocky", .status = AVAILABLE },
  { .id = 1, .name = "Garfield", .status = PENDING },
  { .id = 2, .name = "Rantanplan", .status = SOLD }
};
//! [array]

// Returns a textual description of the supplied error code
const char * pet_error_message(pet_error code) {
  switch (code) {
    case OK: return "OK";
    case PET_NOT_FOUND: return "Pet not found";
    case PET_NOT_AVAILABLE: return "Pet not available";
    case PET_ALREADY_SOLD: return "Pet already sold";
    default: return "Unknown error";
  }
}

// Returns a textual representation of the supplied status
const char * pet_status_name(pet_status status) {
  switch (status) {
    case AVAILABLE: return "Available";
    case PENDING: return "Pending";
    case SOLD: return "Sold";
    default: return "Unknown pet status";
  }
}

// Returns a pet by id
RESULT(Pet, pet_error) find_pet(int pet_id) {
  for (int index = 0; index < sizeof(pets) / sizeof(pets[0]); index++) {
    Pet pet = &pets[index];
    if (PET_ID(pet) == pet_id) {
      return (RESULT(Pet, pet_error)) RESULT_SUCCESS(pet);
    }
  }
  return (RESULT(Pet, pet_error)) RESULT_FAILURE(PET_NOT_FOUND);
}

// Sets the status of the supplied pet to SOLD (if available)
RESULT(Pet, pet_error) buy_pet(Pet pet) {
  if (PET_STATUS(pet) != AVAILABLE) {
    return (RESULT(Pet, pet_error)) RESULT_FAILURE(PET_NOT_AVAILABLE);
  }
  PET_STATUS(pet) = SOLD;
  return (RESULT(Pet, pet_error)) RESULT_SUCCESS(pet);
}

//! [source]

#define find_pet find_pet_early_attempt

//! [find_pet_early_attempt]
// Returns a pet by id
Pet find_pet(int pet_id) {
  for (int index = 0; index < sizeof(pets) / sizeof(pets[0]); index++) {
    Pet pet = &pets[index];
    if (PET_ID(pet) == pet_id) {
      return pet;
    }
  }
  return NULL;
}
//! [find_pet_early_attempt]

#undef find_pet
