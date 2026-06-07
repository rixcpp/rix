# rix/debug

Debug printing, formatting, logging, and inspection utilities for Rix.

`rix/debug` is part of Rix, the userland package layer for the Vix.cpp ecosystem.

The source code lives in its own repository. This folder only keeps the official package entry used by the Rix umbrella repository.

## Install

```bash
vix add @rix/debug
vix install
```

## Use

```cpp
#include <rix/debug.hpp>

int main()
{
  rixlib::debug::Debug debug;

  debug.print("Hello {}", "Rix");

  auto text = debug.format("Package: {}", "rix/debug");

  debug.log("loaded {} rows", 3);
  debug.log.warn("slow request: {}ms", 120);

  debug.inspect(text);
}
```

## Repository

```txt
https://github.com/rixcpp/debug
```

## Package

```txt
rix/debug
```

## Namespace

```cpp
rixlib::debug
```

## CMake target

```cmake
rix::debug
```

## Manifest

```txt
packages/debug/vix.json
```

## Role in Rix

Rix does not embed package source code.

The real library lives in:

```txt
github.com/rixcpp/debug
```

The Rix facade mounts this package as:

```cpp
rix.debug.print(...)
rix.debug.format(...)
rix.debug.log(...)
rix.debug.inspect(...)
```
