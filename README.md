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

  auto auth = rix.auth.memory();

  auto registered = auth.register_user({
      "ada@example.com",
      "correct-password"});

  if (registered.ok())
  {
    rix.debug.print("registered:", registered.value().email());
  }

  return 0;
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
@rix/auth
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
rix.auth.memory(...)
rix.auth.database(...)
rix.auth.password.hash(...)
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
| `@rix/auth`  | `rix.auth`  | Production-oriented authentication for Vix C++ applications.   |

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

## Auth example

```cpp
#include <rix.hpp>

int main()
{
  auto auth = rix.auth.memory();
  auto registered = auth.register_user(rixlib::auth::RegisterRequest{"ada@example.com","correct-password"});

  if (registered.failed())
  {
    rix.debug.eprint("auth error:",rixlib::auth::to_string(registered.error().code()),registered.error().message());
    return 1;
  }

  rix.debug.print("registered user:", registered.value().email());
  auto login = auth.login(rixlib::auth::LoginRequest{"ada@example.com", "correct-password"});

  if (login.failed())
  {
    rix.debug.eprint("auth error:", rixlib::auth::to_string(login.error().code()),login.error().message());
    return 1;
  }

  rix.debug.print("login successful");
  rix.debug.print("session:", login.value().session.id());
  rix.debug.print("token issuer:", login.value().token.issuer());

  return 0;
}
```

## Auth password example

```cpp
#include <rix.hpp>

int main()
{
  auto hashed = rix.auth.password.hash("correct-password");

  if (hashed.failed())
  {
    rix.debug.eprint(
        "auth error:",
        rixlib::auth::to_string(hashed.error().code()),
        hashed.error().message());

    return 1;
  }

  const bool valid = rix.auth.password.verify(
      "correct-password",
      hashed.value());

  const bool invalid = rix.auth.password.verify(
      "wrong-password",
      hashed.value());

  rix.debug.print("valid password:", valid ? "yes" : "no");
  rix.debug.print("wrong password:", invalid ? "yes" : "no");

  return valid && !invalid ? 0 : 1;
}
```

## Auth facade API

```cpp
rix.auth.memory()
rix.auth.memory(config)

rix.auth.database(db)
rix.auth.database(db, config)

rix.auth.create(users, sessions)
rix.auth.create(users, sessions, config)

rix.auth.password.hash(...)
rix.auth.password.verify(...)
rix.auth.password.hasher()

rix.auth.config.development()
rix.auth.config.production()

rix.auth.version()
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

And:

```bash
vix add @rix/auth
vix install
```

```cpp
#include <rix/auth.hpp>

int main()
{
  rixlib::auth::MemoryUserStore users;
  rixlib::auth::MemorySessionStore sessions;

  rixlib::auth::Auth auth{
      users,
      sessions,
      rixlib::auth::AuthConfig::development()};

  auto registered = auth.register_user({
      "ada@example.com",
      "correct-password"});

  return registered.ok() ? 0 : 1;
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
│   ├── debug.cpp
│   └── auth/
│       ├── 01_memory_register_login.cpp
│       ├── 02_password_hash.cpp
│       ├── 03_session_refresh_logout.cpp
│       └── 04_token_issue.cpp
├── tests/
│   └── rix_tests.cpp
├── packages/
│   ├── csv/
│   │   ├── README.md
│   │   └── vix.json
│   ├── debug/
│   │   ├── README.md
│   │   └── vix.json
│   └── auth/
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
packages/auth
```

The real source code of each independent package lives in its own repository:

```txt
https://github.com/rixcpp/csv
https://github.com/rixcpp/debug
https://github.com/rixcpp/auth
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
vix run rix_example_auth_01_memory_register_login
vix run rix_example_auth_02_password_hash
vix run rix_example_auth_03_session_refresh_logout
vix run rix_example_auth_04_token_issue
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

Rix keeps packages modular while still offering one clean entry point for users who want the full userland layer.

## Current facade API

```cpp
rix.csv.parse(...)
rix.csv.write(...)

rix.debug.print(...)
rix.debug.eprint(...)
rix.debug.dprint(...)
rix.debug.sprint(...)
rix.debug.format(...)
rix.debug.log(...)
rix.debug.inspect(...)

rix.auth.memory(...)
rix.auth.database(...)
rix.auth.create(...)
rix.auth.password.hash(...)
rix.auth.password.verify(...)
rix.auth.config.development(...)
rix.auth.config.production(...)
```

## License

MIT
