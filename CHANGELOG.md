# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

### Changed

### Fixed

## [1.0.0] - 2026-07-15

### Added

- Initial public release of SBK_Buttons.
- Non-blocking software debouncing.
- Configurable debounce delay with a 50 ms default.
- Active-low and active-high button support.
- Internal pull-up support for active-low buttons.
- Support for active-low buttons using an external pull-up resistor.
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

[Unreleased]: https://github.com/sbarabe/SBK_Buttons/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/sbarabe/SBK_Buttons/releases/tag/v1.0.0