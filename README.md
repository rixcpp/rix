# Rix

Rix is the unified userland library layer for Vix.cpp.

It gives Vix C++ projects a single optional facade object:

```cpp
#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");

  auto table = rix.csv.parse("name,language\nAda,C++\n");

  rix.debug.log("loaded {} rows", table.size());
}
```

Rix does not replace Vix.

Vix provides the runtime, CLI, build workflow, registry integration, and core foundations.

Rix provides optional userland packages and a unified facade over them.

## Design

Rix is built around two levels.

```txt
@rix/csv
@rix/debug
@rix/config
@rix/table
```

These are independent packages.

```txt
@rix/rix
```

This is the unified facade package.

The facade mounts independent packages into one object-style API:

```cpp
rix.csv.parse(...)
rix.debug.print(...)
rix.debug.format(...)
rix.debug.log(...)
rix.debug.inspect(...)
```

## Install

```bash
vix add @rix/rix
vix install
```

## Use

```cpp
#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");

  const auto message = rix.debug.format("Package: {}", "rix/rix");

  rix.debug.log("message: {}", message);

  return 0;
}
```

## Current modules

| Package      | Facade API  | Description                                                    |
| ------------ | ----------- | -------------------------------------------------------------- |
| `@rix/csv`   | `rix.csv`   | Small CSV reader and writer for Vix C++ projects.              |
| `@rix/debug` | `rix.debug` | Debug printing, formatting, logging, and inspection utilities. |

## CSV example

```cpp
#include <rix.hpp>
#include <string>

int main()
{
  const std::string input =
      "name,language\n"
      "Ada,C++\n"
      "Gaspard,Vix\n";

  const auto table = rix.csv.parse(input);

  rix.debug.log("loaded {} rows", table.size());

  for (const auto &row : table)
  {
    for (const auto &field : row)
    {
      rix.debug.print(field);
    }
  }

  return 0;
}
```

## Debug example

```cpp
#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");

  auto text = rix.debug.format("Package: {}", "rix/rix");

  rix.debug.log("loaded {} APIs", 4);
  rix.debug.log.warn("slow path: {}ms", 120);

  rix.debug.inspect(text);

  return 0;
}
```

## Print and format

`rix.debug.print` does not replace `{}` placeholders.

It prints values separated by spaces:

```cpp
rix.debug.print("Hello", "Rix");
rix.debug.print(1, 2, 3);
```

Output:

```txt
Hello Rix
1 2 3
```

For placeholder formatting, use `rix.debug.format`:

```cpp
auto text = rix.debug.format("Hello {}", "Rix");
rix.debug.print(text);
```

Or use `rix.debug.log` directly:

```cpp
rix.debug.log("Hello {}", "Rix");
```

## Independent packages

Each Rix module can also be used independently.

For example:

```bash
vix add @rix/csv
vix install
```

```cpp
#include <rix/csv.hpp>

int main()
{
  rixlib::csv::Csv csv;
  auto table = csv.parse("name,language\nAda,C++\n");

  return 0;
}
```

And:

```bash
vix add @rix/debug
vix install
```

```cpp
#include <rix/debug.hpp>

int main()
{
  rixlib::debug::Debug debug;

  debug.print("Hello", "Rix");
  debug.log("loaded {} rows", 3);

  return 0;
}
```

## Repository layout

```txt
rix/
├── include/
│   └── rix.hpp
├── examples/
│   ├── basic.cpp
│   ├── csv.cpp
│   └── debug.cpp
├── tests/
│   └── rix_tests.cpp
├── packages/
│   ├── csv/
│   │   ├── README.md
│   │   └── vix.json
│   └── debug/
│       ├── README.md
│       └── vix.json
├── CMakeLists.txt
├── vix.json
├── vix.lock
└── README.md
```

## Role of this repository

This repository has two roles.

First, it is the source package for the unified facade:

```txt
@rix/rix
```

Second, it is the official human-readable index of Rix packages:

```txt
packages/csv
packages/debug
```

The real source code of each independent package lives in its own repository:

```txt
https://github.com/rixcpp/csv
https://github.com/rixcpp/debug
```

## Build

```bash
vix install
vix build --build-target all -v
```

## Run examples

Because this repository contains multiple examples, run one explicitly:

```bash
vix run rix_basic
vix run rix_csv_example
vix run rix_debug_example
```

## Tests

```bash
vix tests
```

## Package model

```txt
Vix        -> runtime, CLI, build workflow, registry client
Rix        -> userland libraries and unified facade
Registry   -> package metadata and version resolution
```

Rix keeps packages modular while still offering one clean entry point for users who want the full standard userland layer.

## Current facade API

```cpp
rix.csv.parse(...)
rix.csv.write(...)

rix.debug.print(...)
rix.debug.format(...)
rix.debug.log(...)
rix.debug.inspect(...)
```

## License

MIT
