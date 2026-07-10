# Agent Guidelines

## Scope
These instructions apply to the entire repository unless a directory contains a more specific `AGENTS.md` file.

## Coding conventions
- The firmware and tools are predominantly written in C targeting the SDCC compiler. Preserve the existing formatting style that uses tabs with an 8-space display width (`c-basic-offset: 8`).
- Keep file header comments, licensing notices, and Doxygen-style documentation blocks intact.
- Favour small, self-contained changes that respect the 8-bit microcontroller constraints (watch stack usage, memory footprint, and interrupt safety).

## Build & test expectations
- Use `make` from the `Firmware/` directory to build, and `make install` to ensure the images package correctly. The `tests/test_build.sh` script wraps these steps; run it before submitting changes.
- Ensure any new tests or scripts remain compatible with the GitHub Actions workflow (`.github/workflows/test_build.yml`).

## Miscellaneous
- When adding configuration or board definitions, mirror the structure in `Firmware/include/board_*.h` and document new parameters in `README.markdown` if they impact users.
- Avoid introducing new binary artefacts; place generated firmware under `Firmware/dst/` via the existing build system only.
