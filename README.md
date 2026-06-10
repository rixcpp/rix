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
  auto registered = auth.register_user({"ada@example.com","correct-password"});

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
rix.auth.password.verify(...)
rix.auth.config.production(...)
rix.auth.error.to_string(...)
```

Public examples should prefer the unified `rix` facade.

The lower-level `rixlib` namespace is reserved for package implementation details, independent package usage, and advanced integration code.

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
  auto registered = auth.register_user({"ada@example.com","correct-password"});

  if (registered.failed())
  {
    const auto &error = registered.error();
    rix.debug.eprint("auth error:",rix.auth.error.to_string(error),error.message());

    return 1;
  }

  rix.debug.print("registered user:", registered.value().email());

  auto login = auth.login({"ada@example.com","correct-password"});

  if (login.failed())
  {
    const auto &error = login.error();
    rix.debug.eprint("auth error:",rix.auth.error.to_string(error),error.message());
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
    const auto &error = hashed.error();
    rix.debug.eprint("auth error:",rix.auth.error.to_string(error),error.message());
    return 1;
  }

  const bool valid = rix.auth.password.verify("correct-password",hashed.value());
  const bool invalid = rix.auth.password.verify("wrong-password",hashed.value());

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

rix.auth.managed(users, sessions)
rix.auth.managed(users, sessions, config)

rix.auth.create(users, sessions)
rix.auth.create(users, sessions, config)

rix.auth.password.hash(...)
rix.auth.password.verify(...)
rix.auth.password.accepts(...)
rix.auth.password.hasher()

rix.auth.config.development()
rix.auth.config.production()
rix.auth.config.validate(...)
rix.auth.config.valid(...)

rix.auth.error.to_string(...)
rix.auth.error.make(...)
rix.auth.error.none(...)

rix.auth.stores.memory_users()
rix.auth.stores.memory_sessions()
rix.auth.stores.database_users(db)
rix.auth.stores.database_sessions(db)

rix.auth.version()
```

## Auth service creation

Most applications should use the safe managed APIs.

For local examples, tests, and small applications:

```cpp
auto auth = rix.auth.memory();
```

For durable applications backed by a Vix database:

```cpp
auto auth = rix.auth.database(db);
```

For custom stores where Rix should own the store lifetime:

```cpp
auto users = rix.auth.stores.memory_users();
auto sessions = rix.auth.stores.memory_sessions();

auto auth = rix.auth.managed(std::move(users),std::move(sessions));

if (auth.failed())
{
  const auto &error = auth.error();
  rix.debug.eprint("auth error:",rix.auth.error.to_string(error),error.message());

  return 1;
}
```

`rix.auth.managed(...)` is the preferred custom-store API because it owns the stores inside the returned auth service.

### Advanced: `rix.auth.create(...)`

`rix.auth.create(...)` is an advanced API for caller-owned stores.

It does not own the user store or session store. The caller must ensure both stores live longer than the returned auth service.

Correct usage:

```cpp
auto users = rix.auth.stores.memory_users();
auto sessions = rix.auth.stores.memory_sessions();
auto auth = rix.auth.create(*users,*sessions);
```

In this example, `users` and `sessions` must remain alive while `auth` is used.

For public application code, prefer:

```cpp
auto auth = rix.auth.memory();
```

or:

```cpp
auto auth = rix.auth.database(db);
```

or:

```cpp
auto auth = rix.auth.managed(
    rix.auth.stores.memory_users(),
    rix.auth.stores.memory_sessions()
);
```

Use `create(...)` only when you intentionally want to manage store lifetime yourself.

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
      rixlib::auth::AuthConfig::development()
  };

  auto registered = auth.register_user({
      "ada@example.com",
      "correct-password"
  });

  return registered.ok() ? 0 : 1;
}
```

Independent packages expose their own lower-level APIs.

For the unified public facade, prefer `@rix/rix` and `#include <rix.hpp>`.

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
rix.auth.managed(...)
rix.auth.create(...)
rix.auth.password.hash(...)
rix.auth.password.verify(...)
rix.auth.config.development(...)
rix.auth.config.production(...)
rix.auth.error.to_string(...)
rix.auth.stores.memory_users(...)
rix.auth.stores.memory_sessions(...)
```

## License

MIT
