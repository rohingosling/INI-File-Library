# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A DOS-era C++ INI file reader/writer library, originally written in 1992. Provides a single `INI` class for loading, querying, and saving standard Windows-style INI files with sections, key-value pairs, and semicolon comments.

## Toolchain

- **Compiler:** Borland Turbo C++ / Borland Turbo C++ 3.1 for DOS (16-bit real mode).
- **Memory model:** Uses far-heap allocation (`farmalloc`, `farfree` from `<ALLOC.H>`). Do not replace these with `malloc`/`free` or `new`/`delete` — far-heap functions are required for the DOS large/medium memory models.
- **Standard headers** use uppercase (`<STDIO.H>`, `<STRING.H>`, `<ALLOC.H>`) per Borland convention.
- No build system file (Makefile, CMake, etc.) is present. The library is compiled directly via the Borland IDE or command-line compiler (`bcc`).

## Architecture

The entire library is two files:

- **`ini.h`** — Class declaration and compile-time limits (`INI_MAX_ENTRIES`, `INI_MAX_STRING_SIZE`, `INI_MAX_LINE_SIZE`).
- **`ini.cpp`** — Full implementation: constructor, destructor, `Load`, `GetValue`, `Save`, and private helpers `TrimWhitespace` and `StripQuotes`.

Data is stored in three parallel `char**` arrays (`section_names`, `key_names`, `key_values`), each with up to `INI_MAX_ENTRIES` slots of `INI_MAX_STRING_SIZE` bytes. Lookup is a linear scan.

## Pending Work

The header contains tagged placeholder comments for two unimplemented public methods:

- `{{Add Section}}` — add a new section at runtime.
- `{{Add Key-Value}}` — add a new key-value pair at runtime.

`Save` is declared but not yet implemented in `ini.cpp`.

## Code Style

- Allman brace style with tab indentation.
- Verbose block comments on every method (description, parameters, return values).
- Whitespace-padded expressions: `string [ i ]`, `( char * )`, `INI::Load ( ... )`.
- Semicolons after closing braces of method bodies (`;` after `}`), following the original author's convention — preserve this style.
