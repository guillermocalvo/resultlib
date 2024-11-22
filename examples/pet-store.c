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
#include <assert.h>
#include <result.h>
#include "pet-store.h"

//! [array]
// Available pets in the store
static struct pet pets[] = {
    { .id = 0, .name = "Rocky", .status = AVAILABLE },
    { .id = 1, .name = "Garfield", .status = PENDING },
    { .id = 2, .name = "Rantanplan", .status = SOLD }
};
//! [array]

#define FOREACH(index, array) for (int index = 0; index < sizeof(array) / sizeof(array[0]); index++)

Pet find_pet(int pet_id) {
  FOREACH(index, pets) {
    Pet pet = &pets[index];
    if (PET_ID(pet) == pet_id) {
      return pet;
    }
  }
  return NULL;
}

RESULT(Pet, pet_error) find_pet_embracing_results(int pet_id) {
  FOREACH(index, pets) {
    Pet pet = &pets[index];
    if (PET_ID(pet) == pet_id) {
      return (RESULT(Pet, pet_error)) RESULT_SUCCESS(pet);
    }
  }
  return (RESULT(Pet, pet_error)) RESULT_FAILURE(PET_NOT_FOUND);
}

# define get_pet_status get_pet_status_early_attempt

//! [early_attempt]
// Returns the status of a pet by id
pet_status get_pet_status(int id) {
  Pet pet = find_pet(id);
  return PET_STATUS(pet);
}
//! [early_attempt]

# undef get_pet_status
# define get_pet_status get_pet_status_using_pointers

//! [using_pointers]
// Returns the status of a pet by id
pet_error get_pet_status(int id, pet_status * status) {
  Pet pet = find_pet(id);
  if (pet == NULL) {
    return PET_NOT_FOUND;
  }
  *status = PET_STATUS(pet);
  return OK;
}
//! [using_pointers]

# undef get_pet_status
# define get_pet_status get_pet_status_using_results

//! [using_results]
// Returns the status of a pet by id
RESULT(pet_status, pet_error) get_pet_status(int id) {
  Pet pet = find_pet(id);
  if (pet == NULL) {
    return (RESULT(pet_status, pet_error)) RESULT_FAILURE(PET_NOT_FOUND);
  }
  return (RESULT(pet_status, pet_error)) RESULT_SUCCESS(PET_STATUS(pet));
}
//! [using_results]

# undef get_pet_status
# define get_pet_status get_pet_status_embracing_results
# define find_pet find_pet_embracing_results

//! [embracing_results]
// Returns the status of a pet by id
RESULT(pet_status, pet_error) get_pet_status(int id) {
  RESULT(Pet, pet_error) result = find_pet(id);
  return RESULT_MAP_SUCCESS(result, PET_STATUS, RESULT(pet_status, pet_error));
}
//! [embracing_results]

# undef get_pet_status
# undef find_pet

int main() {
#ifdef NDEBUG
  return 77;
#else
  RESULT(pet_status, pet_error) result1 = get_pet_status_using_results(0);
  assert(RESULT_HAS_SUCCESS(result1));
  assert(RESULT_USE_SUCCESS(result1) == AVAILABLE);
  RESULT(pet_status, pet_error) result2 = get_pet_status_using_results(-1);
  assert(RESULT_HAS_FAILURE(result2));
  assert(RESULT_HAS_FAILURE(result2) == PET_NOT_FOUND);
  RESULT(pet_status, pet_error) result3 = get_pet_status_embracing_results(0);
  assert(RESULT_HAS_SUCCESS(result3));
  assert(RESULT_USE_SUCCESS(result3) == AVAILABLE);
  RESULT(pet_status, pet_error) result4 = get_pet_status_embracing_results(-1);
  assert(RESULT_HAS_FAILURE(result4));
  assert(RESULT_HAS_FAILURE(result4) == PET_NOT_FOUND);
#endif
  return 0;
}
