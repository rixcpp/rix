# Changelog

All notable changes to this project will be documented in this file.

## v0.9.0

### Added

- Added `@rix/pdf` to the unified Rix facade.
- Added `rix.pdf` public API for PDF document generation.
- Added PDF document creation through `rix.pdf.document()`.
- Added PDF saving through `rix.pdf.save(document, path)`.
- Added PDF byte serialization through `rix.pdf.write(document)`.
- Added high-level text PDF helper through `rix.pdf.make_text(...)`.
- Added PDF image helpers through `rix.pdf.image.load_jpeg(...)` and `rix.pdf.image.from_jpeg_bytes(...)`.
- Added PDF error helpers through `rix.pdf.error`.
- Added public PDF examples under `examples/pdf`.

### Changed

- Updated the unified `rix` facade to mount the PDF module as `rix.pdf`.
- Updated README documentation with `@rix/pdf`, `rix.pdf`, PDF examples, and PDF error handling.
- Updated example CMake configuration to build PDF examples.
- Updated package metadata and lock file for the new PDF dependency.

### Notes

- `rix.pdf` is the high-level public API for users of `@rix/rix`.
- Lower-level `rixlib::pdf` APIs remain available for independent package usage and advanced integration.

## v0.7.0

### Added

- Added `@rix/pdf` to the unified Rix facade.
- Added `rix.pdf` public API for PDF document generation.
- Added PDF document creation through `rix.pdf.document()`.
- Added PDF saving through `rix.pdf.save(document, path)`.
- Added PDF byte serialization through `rix.pdf.write(document)`.
- Added high-level text PDF helper through `rix.pdf.make_text(...)`.
- Added PDF image helpers through `rix.pdf.image.load_jpeg(...)` and `rix.pdf.image.from_jpeg_bytes(...)`.
- Added PDF error helpers through `rix.pdf.error`.
- Added PDF examples under `examples/pdf`.
- Added PDF example targets:
  - `rix_pdf_01_basic`
  - `rix_pdf_02_text`
  - `rix_pdf_03_table`
  - `rix_pdf_04_drawing`
  - `rix_pdf_05_metadata`
  - `rix_pdf_06_make_text`
  - `rix_pdf_07_error_handling`

### Changed

- Updated the unified `rix` facade to mount the PDF module as `rix.pdf`.
- Updated public examples to prefer the stable `rix.*` facade API.
- Updated README documentation with `@rix/pdf`, `rix.pdf`, PDF examples, and PDF error handling.
- Updated repository layout documentation to include `examples/pdf` and `packages/pdf`.

### Notes

- `rix.pdf` is the public high-level PDF API for users of `@rix/rix`.
- The lower-level `rixlib::pdf` API remains available for independent package usage and advanced integration.
- PDF writer internals stay hidden behind explicit `PdfResult<T>` and `PdfStatus` values.
