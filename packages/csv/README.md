# rix/csv

Small CSV reader and writer for Vix C++ projects.

`rix/csv` is part of Rix, the userland package layer for the Vix.cpp ecosystem.

The source code lives in its own repository. This folder only keeps the official package entry used by the Rix umbrella repository.

## Install

```bash
vix add @rix/csv
vix install
```

## Use

```cpp
#include <rix/csv.hpp>

int main()
{
  rixlib::csv::Csv csv;
  auto table = csv.parse("name,lang\nAda,C++\n");
}
```

## Run

```bash
vix run main.cpp
```

## Repository

```txt
https://github.com/rixcpp/csv
```

## Package

```txt
rix/csv
```

## Namespace

```cpp
rix::csv
```

## CMake target

```cmake
rix::csv
```

## Manifest

```txt
packages/csv/vix.json
```

## Role in Rix

Rix does not embed package source code.

The real library lives in:

```txt
github.com/rixcpp/csv
```

The Rix umbrella keeps only the public package entry, documentation, and metadata.
