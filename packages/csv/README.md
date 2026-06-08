# @rix/csv

CSV parser and writer for Rix.

`@rix/csv` is a small header-only C++ package for reading, writing, transforming, and inspecting CSV data.

It can be used independently, or through the unified `@rix/rix` facade.

## Installation

```bash
vix add @rix/csv
vix install
```

## Basic usage

```cpp
#include <rix/csv.hpp>

#include <iostream>
#include <string>

int main()
{
  const std::string input =
      "name,language\n"
      "Ada,C++\n"
      "Gaspard,Vix\n";

  const rixlib::csv::Table table = rixlib::csv::parse(input);

  std::cout << "rows: " << table.size() << '\n';

  for (const auto &row : table)
  {
    for (std::size_t i = 0; i < row.size(); ++i)
    {
      if (i > 0)
      {
        std::cout << ' ';
      }

      std::cout << row[i];
    }

    std::cout << '\n';
  }

  return 0;
}
```

Output:

```txt
rows: 3
name language
Ada C++
Gaspard Vix
```

## Parse CSV

```cpp
const std::string input =
    "name,language\n"
    "Ada,C++\n";

const rixlib::csv::Table table = rixlib::csv::parse(input);
```

A table is represented as:

```cpp
using Row = std::vector<std::string>;
using Table = std::vector<Row>;
```

So this CSV:

```txt
name,language
Ada,C++
```

becomes:

```cpp
{
  {"name", "language"},
  {"Ada", "C++"}
}
```

## Write CSV

```cpp
const rixlib::csv::Table table = {
    {"name", "language"},
    {"Ada", "C++"},
    {"Gaspard", "Vix"},
};

const std::string output = rixlib::csv::write(table);
```

Output:

```txt
name,language
Ada,C++
Gaspard,Vix
```

## Write a single row

```cpp
const rixlib::csv::Row row = {"Ada", "C++", "expert"};

const std::string line = rixlib::csv::write_row(row);
```

Output:

```txt
Ada,C++,expert
```

## Parsing options

```cpp
rixlib::csv::Options options{};
options.skip_empty_lines = true;
options.trim_whitespace = true;

const auto table = rixlib::csv::parse(input, options);
```

Available options include:

```cpp
options.separator = ',';
options.quote_char = '"';
options.trim_whitespace = false;
options.skip_empty_lines = false;
options.skip_comments = false;
options.comment_char = '#';
options.max_field_size = 0;
options.max_fields_per_row = 0;
```

You can also transform fields while parsing:

```cpp
rixlib::csv::Options options{};

options.field_transformer = [](std::string &field)
{
  for (char &ch : field)
  {
    ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
  }
};

const auto table = rixlib::csv::parse(input, options);
```

And filter rows:

```cpp
rixlib::csv::Options options{};

options.row_filter = [](const rixlib::csv::Row &row)
{
  return row.size() == 2;
};

const auto table = rixlib::csv::parse(input, options);
```

## Writing options

```cpp
rixlib::csv::WriteOptions options{};
options.separator = ';';
options.line_ending = "\r\n";
options.always_quote = true;

const std::string output = rixlib::csv::write(table, options);
```

Available write options include:

```cpp
options.separator = ',';
options.quote_char = '"';
options.line_ending = "\n";
options.always_quote = false;
options.trim_before_write = false;
```

## Load and save files

```cpp
const rixlib::csv::Table table = rixlib::csv::load("data.csv");

rixlib::csv::save("output.csv", table);
```

## Stream support

Parse from an input stream:

```cpp
std::ifstream file("data.csv", std::ios::binary);

const rixlib::csv::Table table = rixlib::csv::parse(file);
```

Write to an output stream:

```cpp
std::ofstream file("output.csv", std::ios::binary);

rixlib::csv::write_to(file, table);
```

## Dict-style reading

The first row can be treated as a header.

```cpp
const auto table = rixlib::csv::parse(
    "name,language\n"
    "Ada,C++\n"
    "Gaspard,Vix\n");

rixlib::csv::DictReader reader{table};

for (const rixlib::csv::RowView row : reader)
{
  std::cout << row["name"] << " uses " << row["language"] << '\n';
}
```

Output:

```txt
Ada uses C++
Gaspard uses Vix
```

## Select columns

```cpp
const auto selected = rixlib::csv::select_columns(table, {"name"});
```

## Read a column

```cpp
const std::vector<std::string> names = rixlib::csv::column(table, "name");
```

## Filter rows

```cpp
const auto filtered = rixlib::csv::filter_rows(
    table,
    [](const rixlib::csv::Row &row)
    {
      return row.size() >= 2 && row[1] == "C++";
    });
```

## Transform fields

```cpp
const auto transformed = rixlib::csv::transform_fields(
    table,
    [](std::string &field)
    {
      field = "[" + field + "]";
    });
```

## Describe a table

```cpp
std::cout << rixlib::csv::describe(table);
```

Example output:

```txt
csv::Table: 3 row(s), 2 column(s)
  [header]  "name" | "language"
  [1]       "Ada" | "C++"
  [2]       "Gaspard" | "Vix"
```

## Dialect detection

```cpp
const auto dialect = rixlib::csv::sniff(sample);

rixlib::csv::Options options{};
options.separator = dialect.separator;

const auto table = rixlib::csv::parse(full_text, options);
```

## Streaming parser

Use `StreamingParser` when you want to process rows without storing the full table in memory.

```cpp
std::size_t count = 0;

rixlib::csv::StreamingParser parser{
    [&](const rixlib::csv::Row &row)
    {
      ++count;
    }};

parser.parse(input);

std::cout << "rows: " << count << '\n';
```

## Version

```cpp
std::cout << rixlib::csv::version() << '\n';
```

## Unified Rix facade

When used through `@rix/rix`, the package is mounted under `rix.csv`.

```cpp
#include <rix.hpp>

int main()
{
  const auto table = rix.csv.parse("name,language\nAda,C++\n");

  rix.debug.log("loaded {} rows", table.size());

  return 0;
}
```

## Design

`@rix/csv` is header-only and keeps the data model simple.

```cpp
rixlib::csv::Row
rixlib::csv::Table
```

The package exposes free functions such as:

```cpp
rixlib::csv::parse(...)
rixlib::csv::write(...)
rixlib::csv::write_row(...)
rixlib::csv::load(...)
rixlib::csv::save(...)
```

The unified facade package `@rix/rix` can mount these functions as:

```cpp
rix.csv.parse(...)
rix.csv.write(...)
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
