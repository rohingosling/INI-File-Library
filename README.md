# INI File Library

A lightweight C++ library for reading, writing, and manipulating standard Windows-style INI files. Originally written in 1992 for DOS real-mode programs compiled with Borland Turbo C++.

## Features

- Load and parse INI files with sections, key-value pairs, and semicolon comments.
- Query values by section and key.
- Add new sections and key-value pairs at runtime.
- Update existing values in place.
- Save the in-memory state back to disk.
- Build INI files from scratch without loading from a file.
- Uses far-heap allocation for compatibility with DOS large and medium memory models.

## Requirements

- **Compiler:** Borland Turbo C++ 3.1 (or compatible) for DOS.
- **Memory model:** Large (`-ml`) or medium. The library uses `farmalloc` / `farfree` from `<ALLOC.H>`.

## Files

```
ini.h       Class declaration and compile-time limits.
ini.cpp     Full implementation.
test/       Test program, build script, and sample INI file.
```

## Quick Start

### 1. Add the library to your project

Copy `ini.h` and `ini.cpp` into your project directory (or a known include path). Include the header in your source file:

```cpp
#include "ini.h"
```

Compile `ini.cpp` alongside your own source files. No separate build step or library archive is required.

### 2. Read an existing INI file

Given a file called `config.ini`:

```ini
; Application configuration.

[Video]
width      = 640
height     = 480
fullscreen = no

[Audio]
volume = 75
```

Load it and retrieve values:

```cpp
INI configuration;

if ( configuration.Load ( "config.ini" ) == 0 )
{
    char *width  = configuration.GetValue ( "Video", "width" );
    char *volume = configuration.GetValue ( "Audio", "volume" );

    if ( width != NULL )
    {
        printf ( "Width: %s\n", width );
    }

    if ( volume != NULL )
    {
        printf ( "Volume: %s\n", volume );
    }
}
```

### 3. Modify values and save

```cpp
INI configuration;

configuration.Load ( "config.ini" );

// Update an existing key.

configuration.SetValue ( "Audio", "volume", "50" );

// Add a new key to an existing section.

configuration.SetValue ( "Video", "renderer", "VGA" );

// Add a key to a brand new section.

configuration.SetValue ( "Network", "port", "8080" );

// Write everything to disk.

configuration.Save ( "config.ini" );
```

### 4. Build an INI file from scratch

No input file is needed. Create entries directly and save:

```cpp
INI configuration;

configuration.SetValue ( "Database", "host", "localhost" );
configuration.SetValue ( "Database", "port", "3306" );
configuration.SetValue ( "Database", "name", "appdata" );

configuration.Save ( "database.ini" );
```

The resulting file:

```ini
[Database]
host = localhost
port = 3306
name = appdata
```

### 5. Compile

From the Borland command line, compile your program together with `ini.cpp`:

```bat
bcc -ml -I<path_to_ini_h> your_program.cpp <path_to_ini_cpp>\ini.cpp
```

For example, if the library files sit one directory above your source:

```bat
bcc -ml -I.. main.cpp ..\ini.cpp
```

## API Reference

### Constructor / Destructor

| Method   | Description                                                         |
|----------|---------------------------------------------------------------------|
| `INI()`  | Initialises internal pointers to NULL. No memory is allocated.      |
| `~INI()` | Frees all far-heap memory allocated during the lifetime of the object. |

### Public Methods

#### `int Load ( const char *file_name )`

Parses an INI file and stores its contents in memory. Allocates memory on first call if not already allocated.

- **Returns** `0` on success, `-1` if the file cannot be opened.
- Key-value pairs appearing before any section header are ignored.
- Semicolon lines (`;`) are treated as comments and skipped.
- Surrounding double quotes on values are stripped automatically.

#### `char *GetValue ( const char *section, const char *key )`

Retrieves the value for a given section and key. The search is case-sensitive.

- **Returns** a pointer to the value string, or `NULL` if not found.

#### `int AddSection ( const char *section )`

Validates that a section can receive entries. If the section already exists, the call succeeds immediately. If it does not exist, the method verifies that capacity remains.

- **Returns** `0` on success, `-1` if the entry table is full.
- Section headers only appear in saved files when key-value pairs have been added via `SetValue`.

#### `int SetValue ( const char *section, const char *key, const char *value )`

Adds a new key-value pair or updates an existing one. If no entry with the given section and key exists, a new entry is appended. Memory is allocated lazily on first use.

- **Returns** `0` on success, `-1` if the entry table is full and no existing entry matches.

#### `int Save ( const char *file_name )`

Writes all in-memory entries to an INI file, grouped by section. Comments from the original file are not preserved.

- **Returns** `0` on success, `-1` if the file cannot be opened for writing.

## Compile-Time Limits

These constants are defined in `ini.h` and can be adjusted before compilation:

| Constant               | Default | Description                                      |
|------------------------|---------|--------------------------------------------------|
| `INI_MAX_ENTRIES`      | 256     | Maximum number of key-value entries.             |
| `INI_MAX_STRING_SIZE`  | 80      | Maximum length of a section name, key, or value. |
| `INI_MAX_LINE_SIZE`    | 120     | Maximum length of a single line in the INI file. |

## Running the Tests

From the `test` directory:

```bat
build.bat
test.exe
```

The test program exercises all public methods and prints pass/fail results.

## License

This project is provided as-is for educational and archival purposes.
