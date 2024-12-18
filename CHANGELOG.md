
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).


## [Unreleased]

- Refactor `RESULT_IF` macros so `result` doesn't have to be an lvalue.

### Changed

- Macro `RESULT_IF_SUCCESS`
- Macro `RESULT_IF_FAILURE`
- Macro `RESULT_IF_SUCCESS_OR_ELSE`


## [0.1.0]

Initial development release.

### Added

- Macro `RESULT_VERSION`
- Macro `RESULT_TAG`
- Macro `RESULT_STRUCT_TAG`
- Macro `RESULT_STRUCT`
- Macro `RESULT`
- Macro `RESULT_SUCCESS`
- Macro `RESULT_FAILURE`
- Macro `RESULT_HAS_SUCCESS`
- Macro `RESULT_HAS_FAILURE`
- Macro `RESULT_USE_SUCCESS`
- Macro `RESULT_USE_FAILURE`
- Macro `RESULT_GET_SUCCESS`
- Macro `RESULT_GET_FAILURE`
- Macro `RESULT_OR_ELSE`
- Macro `RESULT_OR_ELSE_MAP`
- Macro `RESULT_IF_SUCCESS`
- Macro `RESULT_IF_FAILURE`
- Macro `RESULT_IF_SUCCESS_OR_ELSE`
- Macro `RESULT_FILTER`
- Macro `RESULT_FILTER_MAP`
- Macro `RESULT_RECOVER`
- Macro `RESULT_RECOVER_MAP`
- Macro `RESULT_MAP_SUCCESS`
- Macro `RESULT_MAP_FAILURE`
- Macro `RESULT_MAP`
- Macro `RESULT_FLAT_MAP_SUCCESS`
- Macro `RESULT_FLAT_MAP_FAILURE`
- Macro `RESULT_FLAT_MAP`
- Macro `RESULT_DEBUG_FUNC`
- Macro `RESULT_DEBUG_FILE`
- Macro `RESULT_DEBUG_LINE`


[Unreleased]: https://github.com/guillermocalvo/resultlib/compare/main...develop
[0.1.0]: https://github.com/guillermocalvo/resultlib/releases/tag/0.1.0
