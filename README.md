# Rix

Rix is the unified userland library layer for Vix.cpp.

It gives Vix C++ projects a set of optional userland packages and a single clean facade object:

```cpp
#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");
  auto table = rix.csv.parse("name,language\nAda,C++\n");
  rix.debug.log("loaded {} rows", table.size());

  return 0;
}
```

Rix does not replace Vix.

Vix provides the runtime, CLI, build workflow, registry integration, and core foundations.

Rix provides optional userland packages and a unified facade over them.

---

## Links

- Website: https://vixcpp.com
- Rix Docs: https://rix.vixcpp.com
- Registry: https://registry.vixcpp.com
- Vix Docs: https://docs.vixcpp.com

---

## Design

Rix is built around two levels.

### Independent packages

```txt
@rix/csv
@rix/debug
@rix/auth
@rix/pdf
@rix/config
@rix/table
```

These packages are independent.

They can be installed and used directly when an application only needs one package.

### Unified facade package

```txt
@rix/rix
```

This package provides the optional unified facade:

```cpp
rix.csv.parse(...)
rix.debug.print(...)
rix.auth.memory(...)
rix.pdf.document()
```

The facade is for applications that want one clean object-style API.

Public examples should prefer the unified `rix` facade.

The lower-level `rixlib` namespace is reserved for package implementation details, independent package usage, and advanced integration code.

---

## Package model

```txt
Vix        -> runtime, CLI, build workflow, registry client, core modules
Rix        -> userland libraries and optional unified facade
Registry   -> package metadata and version resolution
```

Rix keeps packages modular while still offering one clean entry point for users who want the full userland layer.

---

## Install

Install the unified facade:

```bash
vix add @rix/rix
vix install
```

Or install an independent package:

```bash
vix add @rix/csv
vix install
```

```bash
vix add @rix/debug
vix install
```

```bash
vix add @rix/auth
vix install
```

```bash
vix add @rix/pdf
vix install
```

---

## Use the unified facade

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

---

## Lightweight facade usage

By default, `#include <rix.hpp>` enables all current mounted facade modules for backward compatibility.

```cpp
#include <rix.hpp>

int main()
{
  rix.csv.parse("name,language\nAda,C++\n");
  rix.debug.print("Hello", "Rix");

  auto auth = rix.auth.memory();

  auto doc = rix.pdf.document();

  return 0;
}
```

For lighter usage, define only the modules you want before including `rix.hpp`.

```cpp
#define RIX_ENABLE_CSV
#include <rix.hpp>

int main()
{
  auto table = rix.csv.parse("name,language\nAda,C++\n");

  return table.empty() ? 1 : 0;
}
```

Multiple modules can be enabled together:

```cpp
#define RIX_ENABLE_CSV
#define RIX_ENABLE_DEBUG
#include <rix.hpp>

int main()
{
  auto table = rix.csv.parse("name,language\nAda,C++\n");

  rix.debug.log("loaded {} rows", table.size());

  return 0;
}
```

Available facade macros:

```txt
RIX_ENABLE_CSV
RIX_ENABLE_DEBUG
RIX_ENABLE_AUTH
RIX_ENABLE_PDF
```

If no `RIX_ENABLE_*` macro is defined, all current facade modules are enabled.

This keeps existing code working:

```cpp
#include <rix.hpp>
```

This enables only CSV:

```cpp
#define RIX_ENABLE_CSV
#include <rix.hpp>
```

This enables CSV and Debug:

```cpp
#define RIX_ENABLE_CSV
#define RIX_ENABLE_DEBUG
#include <rix.hpp>
```

Do not define facade macros after including `rix.hpp`.

Wrong:

```cpp
#include <rix.hpp>

#define RIX_ENABLE_CSV
#include <rix.hpp>
```

Correct:

```cpp
#define RIX_ENABLE_CSV
#include <rix.hpp>
```

---

## Current modules

| Package      | Facade API  | Description                                                    |
| ------------ | ----------- | -------------------------------------------------------------- |
| `@rix/csv`   | `rix.csv`   | Small CSV reader and writer for Vix C++ projects.              |
| `@rix/debug` | `rix.debug` | Debug printing, formatting, logging, and inspection utilities. |
| `@rix/auth`  | `rix.auth`  | Production-oriented authentication for Vix C++ applications.   |
| `@rix/pdf`   | `rix.pdf`   | PDF generation and document utilities for Vix C++ apps.        |

---

## Full facade example

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

  auto doc = rix.pdf.document();

  auto &page = doc.add_page();

  page.text(
      page.x_left(),
      page.y_top(),
      "Hello from rix.pdf");

  auto saved = rix.pdf.save(doc, "hello.pdf");

  if (saved.ok())
  {
    rix.debug.print("created:", "hello.pdf");
  }

  return 0;
}
```

---

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

---

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

---

## Auth example

```cpp
#include <rix.hpp>

int main()
{
  auto auth = rix.auth.memory();

  auto registered = auth.register_user({
      "ada@example.com",
      "correct-password"});

  if (registered.failed())
  {
    const auto &error = registered.error();

    rix.debug.eprint(
        "auth error:",
        rix.auth.error.to_string(error),
        error.message());

    return 1;
  }

  rix.debug.print("registered user:", registered.value().email());

  auto login = auth.login({
      "ada@example.com",
      "correct-password"});

  if (login.failed())
  {
    const auto &error = login.error();

    rix.debug.eprint(
        "auth error:",
        rix.auth.error.to_string(error),
        error.message());

    return 1;
  }

  rix.debug.print("login successful");
  rix.debug.print("session:", login.value().session.id());
  rix.debug.print("token issuer:", login.value().token.issuer());

  return 0;
}
```

---

## Auth password example

```cpp
#include <rix.hpp>

int main()
{
  auto hashed = rix.auth.password.hash("correct-password");

  if (hashed.failed())
  {
    const auto &error = hashed.error();

    rix.debug.eprint(
        "auth error:",
        rix.auth.error.to_string(error),
        error.message());

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

---

## PDF example

```cpp
#include <rix.hpp>

int main()
{
  auto doc = rix.pdf.document();

  auto &page = doc.add_page();

  page.text(
      page.x_left(),
      page.y_top(),
      "Hello from rix.pdf");

  page.text(
      page.x_left(),
      page.y_top() - 30.0F,
      "This PDF was generated through the unified Rix facade.");

  auto saved = rix.pdf.save(doc, "rix_pdf_basic.pdf");

  if (saved.failed())
  {
    const auto &error = saved.error();

    rix.debug.eprint(
        "pdf error:",
        rix.pdf.error.to_string(error),
        error.message());

    return 1;
  }

  rix.debug.print("created:", "rix_pdf_basic.pdf");

  return 0;
}
```

---

## PDF text example

```cpp
#include <rix.hpp>

int main()
{
  auto doc = rix.pdf.document();

  doc.set_title("Rix PDF Text Example");
  doc.set_author("Rix");

  auto &page = doc.add_page();

  auto y = page.heading(
      page.x_left(),
      page.y_top(),
      "Rix PDF",
      1);

  y -= 10.0F;

  page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "Rix gives Vix C++ projects a unified userland facade. "
      "The PDF module keeps the public API simple while the writer internals stay hidden.");

  auto saved = rix.pdf.save(doc, "rix_pdf_text.pdf");

  if (saved.failed())
  {
    const auto &error = saved.error();

    rix.debug.eprint(
        "pdf error:",
        rix.pdf.error.to_string(error),
        error.message());

    return 1;
  }

  return 0;
}
```

---

## PDF table example

```cpp
#include <rix.hpp>

int main()
{
  auto doc = rix.pdf.document();

  auto &page = doc.add_page();

  auto y = page.heading(
      page.x_left(),
      page.y_top(),
      "Project table",
      1);

  y -= 20.0F;

  rixlib::pdf::Table table;

  table.set_column_widths({
      160.0F,
      160.0F,
      160.0F});

  table.add_header({
      "Name",
      "Language",
      "Project"});

  table.add_row({
      "Ada",
      "C++",
      "Rix"});

  table.add_row({
      "Gaspard",
      "C++",
      "Vix.cpp"});

  page.table(
      page.x_left(),
      y,
      table);

  auto saved = rix.pdf.save(doc, "rix_pdf_table.pdf");

  return saved.ok() ? 0 : 1;
}
```

---

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

---

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

auto auth = rix.auth.managed(
    std::move(users),
    std::move(sessions));

if (auth.failed())
{
  const auto &error = auth.error();

  rix.debug.eprint(
      "auth error:",
      rix.auth.error.to_string(error),
      error.message());

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

auto auth = rix.auth.create(
    *users,
    *sessions);
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
    rix.auth.stores.memory_sessions());
```

Use `create(...)` only when you intentionally want to manage store lifetime yourself.

---

## PDF facade API

```cpp
rix.pdf.document()
rix.pdf.document(page_size, margins)

rix.pdf.write(document)
rix.pdf.save(document, "output.pdf")
rix.pdf.make_text("output.pdf", "content", "title")

rix.pdf.error.to_string(error)
rix.pdf.error.make(code, message)
rix.pdf.error.none()

rix.pdf.image.load_jpeg("image.jpg")
rix.pdf.image.from_jpeg_bytes(bytes)

rix.pdf.writer.write(document)
rix.pdf.writer.save(document, "output.pdf")
rix.pdf.writer.create()

rix.pdf.version()
```

---

## PDF error handling

`rix.pdf` uses explicit result values for normal failures.

```cpp
auto saved = rix.pdf.save(doc, "output.pdf");

if (saved.failed())
{
  const auto &error = saved.error();

  rix.debug.eprint(
      "pdf error:",
      rix.pdf.error.to_string(error),
      error.message());

  return 1;
}
```

For operations that return data:

```cpp
auto bytes = rix.pdf.write(doc);

if (bytes.ok())
{
  rix.debug.print("pdf bytes:", bytes.value().size());
}
```

---

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

---

## Independent packages

Each Rix package can also be used independently.

### CSV

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

  return table.empty() ? 1 : 0;
}
```

### Debug

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

### Auth

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

### PDF

```bash
vix add @rix/pdf
vix install
```

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();

  auto doc = pdf.document();

  auto &page = doc.add_page();

  page.text(
      page.x_left(),
      page.y_top(),
      "Hello from rix/pdf");

  auto saved = pdf.save(doc, "hello.pdf");

  return saved.ok() ? 0 : 1;
}
```

Independent packages expose their own lower-level APIs.

For the unified public facade, prefer `@rix/rix` and `#include <rix.hpp>`.

---

## Repository layout

```txt
rix/
├── include/
│   └── rix.hpp
├── examples/
│   ├── basic.cpp
│   ├── csv.cpp
│   ├── debug.cpp
│   ├── auth/
│   │   ├── 01_memory_register_login.cpp
│   │   ├── 02_password_hash.cpp
│   │   ├── 03_session_refresh_logout.cpp
│   │   └── 04_token_issue.cpp
│   └── pdf/
│       ├── 01_basic.cpp
│       ├── 02_text.cpp
│       ├── 03_table.cpp
│       ├── 04_drawing.cpp
│       ├── 05_metadata.cpp
│       ├── 06_make_text.cpp
│       └── 07_error_handling.cpp
├── tests/
│   └── rix_tests.cpp
├── packages/
│   ├── csv/
│   │   ├── README.md
│   │   └── vix.json
│   ├── debug/
│   │   ├── README.md
│   │   └── vix.json
│   ├── auth/
│   │   ├── README.md
│   │   └── vix.json
│   └── pdf/
│       ├── README.md
│       └── vix.json
├── CMakeLists.txt
├── vix.json
├── vix.lock
└── README.md
```

---

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
packages/pdf
```

The real source code of each independent package lives in its own repository:

```txt
https://github.com/rixcpp/csv
https://github.com/rixcpp/debug
https://github.com/rixcpp/auth
https://github.com/rixcpp/pdf
```

---

## Build

```bash
vix install
vix build --build-target all -v
```

---

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

vix run rix_pdf_01_basic
vix run rix_pdf_02_text
vix run rix_pdf_03_table
vix run rix_pdf_04_drawing
vix run rix_pdf_05_metadata
vix run rix_pdf_06_make_text
vix run rix_pdf_07_error_handling
```

---

## Tests

```bash
vix tests
```

---

## Rix roadmap

Rix should not duplicate Vix Core modules.

If a feature already exists in Vix Core, Rix may provide a higher-level application library around it, but not a duplicate.

```txt
Vix = core runtime and primitives
Rix = optional userland libraries
```

Existing Vix Core modules such as `json`, `fs`, `path`, `time`, `env`, `crypto`, `db`, `orm`, `kv`, `net`, `process`, `threadpool`, `validation`, `middleware`, `websocket`, `template`, `log`, `error`, `async`, `cache`, `io`, and `os` should not be copied directly into Rix.

Rix packages should focus on application-level libraries built on top of Vix.

### Current direction

```txt
@rix/debug
@rix/csv
@rix/auth
@rix/pdf
@rix/table
@rix/config
@rix/rix
```

### Production app packages

```txt
@rix/password
@rix/session
@rix/token
@rix/repository
@rix/migration
@rix/api
@rix/form
@rix/upload
@rix/rate-limit
```

### Reliability packages

```txt
@rix/health
@rix/status
@rix/metrics
@rix/audit
@rix/events
@rix/retry
@rix/backoff
@rix/idempotency
@rix/outbox
```

### Developer tooling packages

```txt
@rix/console
@rix/progress
@rix/bench
@rix/test
@rix/mock
@rix/fake
```

---

## Package rules

Every Rix package should follow these principles:

- small public API
- clear documentation
- simple examples
- independent installation
- stable include path
- stable namespace
- no hidden heavy dependency
- usable without the unified facade
- compatible with the unified facade when installed

---

## Naming convention

Package name:

```txt
@rix/name
```

Include path:

```cpp
#include <rix/name.hpp>
```

Namespace:

```cpp
rixlib::name
```

Facade access:

```cpp
rix.name
```

Examples:

```txt
Package  : @rix/csv
Header   : <rix/csv.hpp>
Namespace: rixlib::csv
Facade   : rix.csv
```

```txt
Package  : @rix/auth
Header   : <rix/auth.hpp>
Namespace: rixlib::auth
Facade   : rix.auth
```

```txt
Package  : @rix/pdf
Header   : <rix/pdf.hpp>
Namespace: rixlib::pdf
Facade   : rix.pdf
```

---

## Main rule

```txt
If it is a primitive, it belongs in Vix.
If it is an application helper, it belongs in Rix.
If it is a complete reliability framework, it belongs in Cnerium.
```

And:

```txt
One application problem = one small Rix package.
Many Rix packages = one optional rix.* facade.
```

---

## License

MIT
