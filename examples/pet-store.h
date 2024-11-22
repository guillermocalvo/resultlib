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

//! [types]
// Pet status in the store
typedef enum pet_status { AVAILABLE, PENDING, SOLD } pet_status;

// Represents a pet
typedef struct pet { int id; const char * name; pet_status status; } * Pet;

// Convenience macros
#define PET_ID(pet) pet->id
#define PET_NAME(pet) pet->name
#define PET_STATUS(pet) pet->status

// Pet error codes
typedef enum pet_error { OK, PET_NOT_FOUND, PET_NOT_AVAILABLE, PET_ALREADY_SOLD } pet_error;
//! [types]

RESULT_STRUCT(Pet, pet_error);
RESULT_STRUCT(pet_status, pet_error);
