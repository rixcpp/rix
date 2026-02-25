# Changelog

All notable changes to **Rix (umbrella)** will be documented in this file.

This project follows **Semantic Versioning** (SemVer).

📘 **README**: https://github.com/rixcpp/rix/blob/v0.2.0/README.md

## v0.4.0

### Added
- Top-level `CMakePresets.json`
- Unified testing workflow via CTest presets
- Header-only refactor for `rix::io`

### Changed
- Refined umbrella `CMakeLists.txt`
- Improved module wiring and export consistency
- Updated README structure and documentation clarity

### Removed
- Legacy `file.cpp` implementation
- Old file-specific tests replaced by unified `test_basic.cpp`

### Notes
This release focuses on structural stability, cleaner module boundaries,
and predictable testing behavior across the Rix ecosystem.

# Rix v0.3.1

## Fixed

- Corrected README header rendering issue (HTML table/image display)

No functional or structural changes.

---
# Rix v0.3.0

## Overview

This release restructures the Rix umbrella project and clarifies its long-term positioning as the foundational standard library of Vix.

---

## Changed

- Removed `rix-` prefix from module directories
- Renamed submodules to align with public repository naming (`io`, `json`, etc.)
- Updated umbrella CMake configuration to reflect new structure
- Cleaned example paths
- Modernized and simplified module wiring

---

## Documentation

- Complete strategic rewrite of the main README
- Clarified Rix positioning within the Vix ecosystem
- Defined long-term vision and philosophy
- Added "What Rix will never become" section

---

## Internal

- Submodule structure cleanup
- Improved naming consistency across the project
- Improved installation/export consistency

---

## Notes

This release does not introduce breaking API changes.

It strengthens structural coherence and prepares Rix for long-term stability within the Vix ecosystem.

## [v0.2.0] — 2025-12-27

### 🔄 Changed

- Updated `modules/rix-io` submodule to **v1.0.0** (first stable release of rix-io).
  - Stabilized IO API (File/Buffer/reader/writer/util)
  - Adopted collision-free naming conventions (STL-safe)
  - Added/updated canonical examples and aligned tests

### 📦 Submodules

- `rix-io`: v1.0.0

---

## [v0.1.2] — (previous)

## [v0.1.1] — (previous)

## [v0.1.0] — (previous)
