# @rix/debug

Debug utilities for Rix.

`@rix/debug` provides a small set of developer-focused tools for C++ projects:

- formatted strings
- simple logging
- value inspection
- print helpers

It can be used as an independent Rix package, or through the unified `@rix/rix` facade.

## Installation

```bash
vix add @rix/debug
vix install
```

## Basic usage

```cpp
#include <rix/debug.hpp>

int main()
{
  rixlib::debug::Debug debug{};

  debug.print("Hello", "Rix");

  auto text = debug.format("Package: {}", "rix/debug");

  debug.log("loaded {} rows", 3);
  debug.log.warn("slow request: {}ms", 120);

  debug.inspect(text);

  return 0;
}
```

Output:

```txt
Hello Rix
[debug] loaded 3 rows
[warn] slow request: 120ms
Package: rix/debug
```

## Formatting

`debug.format` supports simple placeholder-based formatting.

```cpp
auto message = debug.format("Hello {}", "Rix");
auto result = debug.format("{0} + {0} = {1}", 2, 4);
auto escaped = debug.format("{{ value }} = {}", 42);
```

Supported placeholders:

```txt
{}   automatic argument indexing
{0}  explicit positional indexing
{{   escaped opening brace
}}   escaped closing brace
```

Format specifiers such as `{:>10}` or `{:.2f}` are intentionally not supported.

## Logging

```cpp
debug.log("loaded {} rows", 3);
debug.log.info("server started");
debug.log.warn("slow request: {}ms", 120);
debug.log.error("failed: {}", "timeout");
```

Output:

```txt
[debug] loaded 3 rows
[info] server started
[warn] slow request: 120ms
[error] failed: timeout
```

## Printing

`debug.print` is not a formatter.

It prints values separated by spaces.

```cpp
debug.print("Hello", "Rix");
debug.print(1, 2, 3);
```

Output:

```txt
Hello Rix
1 2 3
```

For formatted strings, use `debug.format` or `debug.log`.

```cpp
debug.print(debug.format("Hello {}", "Rix"));
```

## Inspection

```cpp
debug.inspect(42);

auto value = debug.inspect.to_string(true);

bool ok = debug.inspect.check(42, 42);
```

Inspection is useful for debugging values, containers, optional values, variants, and other supported C++ types.

## Independent API

You can also use the free functions directly.

```cpp
#include <rix/debug.hpp>

int main()
{
  rixlib::print("Hello", "Rix");

  auto text = rixlib::format("Package: {}", "rix/debug");

  rixlib::inspect(text);

  return 0;
}
```

## Unified Rix facade

When used through `@rix/rix`, the debug package is mounted under `rix.debug`.

```cpp
#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");
  rix.debug.log("loaded {} rows", 3);

  return 0;
}
```

## Design

`@rix/debug` is intentionally small and focused.

It does not try to replace full logging frameworks or formatting libraries. Its role is to provide simple debugging primitives that are easy to use in Rix-based C++ projects.

The package exposes two layers:

```txt
rixlib::format(...)
rixlib::print(...)
rixlib::inspect(...)
```

and the object-style API:

```txt
rixlib::debug::Debug
```

This keeps the package usable on its own while allowing the unified Rix facade to mount it cleanly as:

```txt
rix.debug
```

## Build

```bash
vix build
```

## Run example

```bash
vix run
```

## Tests

```bash
vix tests
```

## License

MIT
