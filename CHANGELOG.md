# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

### Changed

### Fixed

## [1.0.1] - 2026-07-16

### Changed

- Renamed the library files from `Button.h`/`Button.cpp` to `SBK_Button.h`/`SBK_Button.cpp` to avoid filename collisions with other Arduino libraries.
- Existing sketches must update `#include <Button.h>` to `#include <SBK_Button.h>`.

## [1.0.0] - 2026-07-15

### Added

- Initial public release of SBK_Button.
- Non-blocking software debouncing.
- Configurable debounce delay with a 50 ms default.
- Three type-safe button wiring modes through `ButtonMode`:
  internal pull-up, external pull-up, and external pull-down.
- Active-low and active-high button support.
- Continuous pressed and released state queries.
- One-cycle press and release events.
- Configurable long-press threshold with a 1000 ms default.
- Continuous long-press state detection.
- One-cycle long-press event generated once per press.
- Pressed-time and released-time tracking.
- Individual and combined event-clearing functions.
- Arduino Library Manager metadata.
- PlatformIO Registry metadata.
- Installation, wiring, examples, and API documentation.

[Unreleased]: https://github.com/sbarabe/SBK_Button/compare/v1.0.1...HEAD
[1.0.1]: https://github.com/sbarabe/SBK_Button/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/sbarabe/SBK_Button/releases/tag/v1.0.0