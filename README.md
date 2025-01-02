
[![Build Status][BADGE_BUILD_STATUS]][BUILD_STATUS]
[![Quality Gate Status][BADGE_QUALITY_GATE]][QUALITY_GATE]
[![Docs Status][BADGE_DOCS_STATUS]][DOCS]
[![Latest Release][BADGE_LATEST_RELEASE]][LATEST_RELEASE]

![Result Library][LOGO]


## A header-only C library to handle errors elegantly

Wave goodbye to *output parameters*, *sentinel values*, and endless *null checking*! Embrace clean, efficient error
handling today by encapsulating operations that may succeed or fail in a type-safe way.

### Main Features

- **Boost Performance**: Fewer pointer dereferences; rely on optimized single return values
- **Simple API**: Handle success and failure scenarios with just a handful of C macros
- **Streamlined Error Handling**: Reduce the chances of incorrect or inconsistent error handling
- **Safe Execution**: Enforce valid states, eliminating risks like dangling pointers or stale data
- **Enhanced Readability**: Reduce boilerplate code to make your code easier to understand
- **Functional Style**: Avoid side effects and encourage pure, composable functions
- **Lightweight**: Keep your project slim with no extra dependencies
- **Open Source**: Enjoy transparent, permissive Apache 2 licensing
- **Header-Only C Library**: Compatible with C23 standard and modern compilers

> [!TIP]
> This library provides a cleaner, safer, and more modern approach to error handling by combining function result and
> error into a unified return value. It enforces correct usage at the call site, reduces the risk of bugs, and leads to
> more maintainable and extensible code.


## Results in a Nutshell

Result objects represent the outcome of an operation, removing the need for [output parameters][OUTPUT_PARAMETERS],
[sentinel values][SENTINEL_VALUE], and [null checking][NULL_CHECKING]. Operations that succeed produce results
encapsulating a *success* value; operations that fail produce results with a *failure* value. Success and failure can be
represented by whatever types make the most sense for each operation.

Let's use a *pet store* example to show how this library can simplify your code.

Start by defining some data types to represent pets.

```c
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
```

Next, let's say you have an array of pets acting as your "database".

```c
// Available pets in the store
static struct pet pets[] = {
  { .id = 0, .name = "Rocky", .status = AVAILABLE },
  { .id = 1, .name = "Garfield", .status = PENDING },
  { .id = 2, .name = "Rantanplan", .status = SOLD }
};
```

> [!NOTE]
> You'll use a function, `find_pet(id)`, to retrieve pets by their ID. We'll skip its implementation for now.

Suppose you need to write a function to get a pet's status.

![][EXAMPLE_EARLY_ATTEMPT]

> [!WARNING]
> This works... until someone passes an invalid ID. If `find_pet` returns `NULL`, your code could crash unexpectedly.

To fix this, you refactor the function to return an error code and use a pointer to "return" the status.

![][EXAMPLE_USING_POINTERS]

It's safer, but also clunky.

> [!WARNING]
> What if the pointer is `NULL`? Should you return a new error code? Use `assert`? It's starting to feel messy.

Instead of juggling pointers and error codes, **you should return a Result object**.

![][EXAMPLE_USING_RESULTS]

> [!TIP]
> The result encapsulates both success (pet status) and failure (error code) in one clean package. The caller
> immediately knows the function can fail, and you've eliminated the need for a pointer. This is simpler, safer, and
> much easier to read.

Encouraged, you refactor `find_pet` to return a failed result instead of `NULL` when a pet isn't found. Now,
`get_pet_status` can rely on `find_pet` to handle errors and focus on the happy path.

![][EXAMPLE_EMBRACING_RESULTS]

> [!NOTE]
> And just like that, your code becomes robust and maintainable. No more mysterious crashes, no awkward pointer checks.
> Just clean, elegant error handling.

With Results, handling success and failure feels natural, leaving you free to focus on the fun parts of coding.


## Author

Copyright 2025 [Guillermo Calvo][AUTHOR].

[![][GUILLERMO_IMAGE]][GUILLERMO]


## License

This library is licensed under the *Apache License, Version 2.0* (the "License");
you may not use it except in compliance with the License.

You may obtain a copy of the License at <http://www.apache.org/licenses/LICENSE-2.0>

Unless required by applicable law or agreed to in writing, software distributed under the License
is distributed on an "AS IS" BASIS, **WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND**, either express or implied.

See the License for the specific language governing permissions and limitations under the License.


**Permitted:**

- **Commercial Use**: You may use this library and derivatives for commercial purposes.
- **Modification**: You may modify this library.
- **Distribution**: You may distribute this library.
- **Patent Use**: This license provides an express grant of patent rights from contributors.
- **Private Use**: You may use and modify this library without distributing it.

**Required:**

- **License and Copyright Notice**: If you distribute this library you must include a copy of the license and copyright
  notice.
- **State Changes**: If you modify and distribute this library you must document changes made to this library.

**Forbidden:**

- **Trademark use**: This license does not grant any trademark rights.
- **Liability**: The library author cannot be held liable for damages.
- **Warranty**: This library is provided without any warranty.


[AUTHOR]:                       https://github.com/guillermocalvo/
[BADGE_BUILD_STATUS]:           https://github.com/guillermocalvo/resultlib/workflows/Build/badge.svg
[BADGE_DOCS_STATUS]:            https://github.com/guillermocalvo/resultlib/workflows/Docs/badge.svg
[BADGE_LATEST_RELEASE]:         https://img.shields.io/github/v/release/guillermocalvo/resultlib
[BADGE_QUALITY_GATE]:           https://sonarcloud.io/api/project_badges/measure?project=guillermocalvo_resultlib&metric=alert_status
[BUILD_STATUS]:                 https://github.com/guillermocalvo/resultlib/actions?query=workflow%3ABuild
[COMPOUND_LITERALS]:            https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Compound-Literals.html
[DESIGNATED_INITIALIZERS]:      https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Designated-Inits.html
[DOCS]:                         https://result.guillermo.dev/
[EXAMPLE_EARLY_ATTEMPT]:        docs/early-attempt.png
[EXAMPLE_EMBRACING_RESULTS]:    docs/embracing-results.png
[EXAMPLE_USING_POINTERS]:       docs/using-pointers.png
[EXAMPLE_USING_RESULTS]:        docs/using-results.png
[GUILLERMO]:                    https://guillermo.dev/
[GUILLERMO_IMAGE]:              https://guillermo.dev/assets/images/thumb.png
[LATEST_RELEASE]:               https://github.com/guillermocalvo/resultlib/releases/latest
[LOGO]:                         docs/result-logo.svg
[NULL_CHECKING]:                https://en.wikipedia.org/wiki/Nullable_type#Compared_with_null_pointers
[OUTPUT_PARAMETERS]:            https://en.wikipedia.org/wiki/Parameter_(computer_programming)#Output_parameters
[QUALITY_GATE]:                 https://sonarcloud.io/dashboard?id=guillermocalvo_resultlib
[SENTINEL_VALUE]:               https://en.wikipedia.org/wiki/Sentinel_value
[TYPEOF]:                       https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2899.htm
