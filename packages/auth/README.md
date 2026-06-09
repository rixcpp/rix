# rix/auth

`rix/auth` is the official authentication library for Rix and Vix.cpp applications.

It provides a small production-oriented authentication layer for C++ apps:

- user registration
- login
- password hashing
- server-side sessions
- short-lived auth tokens
- logout
- session validation
- memory stores for tests and small apps
- database stores for durable production usage
- explicit `AuthResult<T>` and `AuthStatus` error handling

`rix/auth` is built to use Vix modules instead of reinventing low-level foundations:

- `vix::crypto` for secure random ids and password hashing helpers
- `vix::validation` for input validation
- `vix::time` for timestamps
- `vix::db` for persistent database-backed stores

## Install

Add the package to your Vix project:

```bash
vix add rix/auth
```

Then include it:

```cpp
#include <rix/auth/Auth.hpp>
```

## Basic usage

```cpp
#include <rix/auth/Auth.hpp>
#include <rix/auth/AuthConfig.hpp>
#include <rix/auth/stores/MemorySessionStore.hpp>
#include <rix/auth/stores/MemoryUserStore.hpp>

#include <iostream>
#include <string>

int main()
{
  rixlib::auth::MemoryUserStore users;
  rixlib::auth::MemorySessionStore sessions;

  auto config = rixlib::auth::AuthConfig::development();

  rixlib::auth::Auth auth{
      users,
      sessions,
      config};

  auto registered_user = auth.register_user(
      rixlib::auth::RegisterRequest{
          "ada@example.com",
          "correct-password"});

  if (registered_user.failed())
  {
    std::cerr << registered_user.error().message() << '\n';
    return 1;
  }

  auto login = auth.login(
      rixlib::auth::LoginRequest{
          "ada@example.com",
          "correct-password"});

  if (login.failed())
  {
    std::cerr << login.error().message() << '\n';
    return 1;
  }

  std::cout << "user: " << login.value().user.email() << '\n';
  std::cout << "session: " << login.value().session.id() << '\n';
  std::cout << "token issuer: " << login.value().token.issuer() << '\n';

  return 0;
}
```

Run:

```bash
vix run examples/basic.cpp
```

## Public API

### Main facade

```cpp
#include <rix/auth/Auth.hpp>
```

The main class is:

```cpp
rixlib::auth::Auth
```

It exposes:

- `register_user(...)`
- `login(...)`
- `logout(...)`
- `logout_user(...)`
- `authenticate_session(...)`
- `refresh_session(...)`
- `issue_token(...)`
- `config()`
- `password_hasher()`

## Configuration

Use `AuthConfig` to configure authentication behavior.

```cpp
auto config = rixlib::auth::AuthConfig::production();

config.set_min_password_length(12);
config.set_session_ttl_seconds(60 * 60 * 24 * 7);
config.set_token_ttl_seconds(60 * 10);
config.set_issuer("my-app");
config.set_require_email_verification(true);
config.set_rotate_sessions(true);
```

### Development config

```cpp
auto config = rixlib::auth::AuthConfig::development();
```

Development defaults are useful for local apps, examples, and tests.

### Production config

```cpp
auto config = rixlib::auth::AuthConfig::production();
```

Production defaults are stricter and should be preferred for real applications.

## Register a user

```cpp
auto result = auth.register_user(
    rixlib::auth::RegisterRequest{
        "ada@example.com",
        "correct-password"});

if (result.failed())
{
  std::cerr << result.error().message() << '\n';
  return 1;
}

const auto &user = result.value();
```

Registration validates the email, validates the password policy, hashes the password, creates the user, and stores it through the configured `UserStore`.

## Login

```cpp
auto result = auth.login(
    rixlib::auth::LoginRequest{
        "ada@example.com",
        "correct-password"});

if (result.failed())
{
  std::cerr << result.error().message() << '\n';
  return 1;
}

const auto &login = result.value();

std::cout << login.user.email() << '\n';
std::cout << login.session.id() << '\n';
std::cout << login.token.value() << '\n';
```

A successful login returns:

```cpp
rixlib::auth::LoginResult
```

It contains:

```cpp
User user;
Session session;
Token token;
```

## Authenticate a session

```cpp
auto session = auth.authenticate_session(session_id);

if (session.failed())
{
  std::cerr << session.error().message() << '\n';
  return 1;
}

std::cout << "session user: "
          << session.value().user_id()
          << '\n';
```

A usable session must be:

- valid
- not revoked
- not expired

## Refresh a session

```cpp
auto refreshed = auth.refresh_session(session_id);

if (refreshed.failed())
{
  std::cerr << refreshed.error().message() << '\n';
  return 1;
}
```

Refreshing updates the session expiration and `last_seen_at`.

## Logout

```cpp
auto status = auth.logout(session_id);

if (status.failed())
{
  std::cerr << status.error().message() << '\n';
  return 1;
}
```

Logout revokes the session instead of deleting it.

## Logout all sessions for a user

```cpp
auto status = auth.logout_user(user_id);

if (status.failed())
{
  std::cerr << status.error().message() << '\n';
  return 1;
}
```

This is useful after password changes, account compromise, or admin actions.

## Issue a token

```cpp
auto token = auth.issue_token(user_id);

if (token.failed())
{
  std::cerr << token.error().message() << '\n';
  return 1;
}
```

Tokens are short-lived values attached to a user id and issuer.

## Error handling

`rix/auth` does not throw for normal authentication failures.

It uses:

- `AuthResult<T>`
- `AuthStatus`
- `AuthError`
- `AuthErrorCode`

Example:

```cpp
auto result = auth.login(
    rixlib::auth::LoginRequest{
        "ada@example.com",
        "wrong-password"});

if (result.failed())
{
  if (result.error().code() == rixlib::auth::AuthErrorCode::InvalidCredentials)
  {
    std::cerr << "invalid credentials\n";
  }
}
```

### Error codes

Common error codes include:

- `None`
- `InvalidInput`
- `InvalidEmail`
- `InvalidPassword`
- `UserNotFound`
- `UserAlreadyExists`
- `InvalidCredentials`
- `InvalidSession`
- `SessionExpired`
- `InvalidToken`
- `TokenExpired`
- `InvalidState`
- `StoreError`
- `CryptoError`
- `Unknown`

## Stores

`rix/auth` separates authentication logic from storage.

The main interfaces are:

- `UserStore`
- `SessionStore`

Available store implementations:

- `MemoryUserStore`
- `MemorySessionStore`
- `DbUserStore`
- `DbSessionStore`

## Memory stores

Memory stores are useful for tests, examples, and small temporary apps.

```cpp
#include <rix/auth/stores/MemoryUserStore.hpp>
#include <rix/auth/stores/MemorySessionStore.hpp>

rixlib::auth::MemoryUserStore users;
rixlib::auth::MemorySessionStore sessions;

rixlib::auth::Auth auth{
    users,
    sessions,
    rixlib::auth::AuthConfig::development()};
```

Memory stores do not persist data after the process exits.

## Database stores

Database stores are intended for durable applications.

```cpp
#include <rix/auth/Auth.hpp>
#include <rix/auth/stores/DbUserStore.hpp>
#include <rix/auth/stores/DbSessionStore.hpp>
#include <vix/db/Database.hpp>

int main()
{
  auto database = vix::db::Database::sqlite("data/auth.db");

  rixlib::auth::DbUserStore users{database};
  rixlib::auth::DbSessionStore sessions{database};

  rixlib::auth::Auth auth{
      users,
      sessions,
      rixlib::auth::AuthConfig::production()};

  return 0;
}
```

By default, database stores create their required tables automatically.

### Database tables

`DbUserStore` uses:

```text
rix_auth_users
```

`DbSessionStore` uses:

```text
rix_auth_sessions
```

The stores create the schema automatically when constructed with `create_schema = true`.

```cpp
rixlib::auth::DbUserStore users{database, true};
rixlib::auth::DbSessionStore sessions{database, true};
```

## Password hashing

Use `Auth` for normal application code.

```cpp
auto result = auth.register_user(...);
```

`PasswordHasher` is available for lower-level usage and tests:

```cpp
rixlib::auth::PasswordHasher hasher;

auto hash = hasher.hash("correct-password");

if (hash.ok())
{
  bool valid = hasher.verify("correct-password", hash.value());
}
```

Password hashes are encoded and must never be returned to clients or logged.

## User model

```cpp
rixlib::auth::User
```

Fields include:

- id
- email
- password hash
- email verification state
- active state
- created timestamp
- updated timestamp

Useful methods:

- `valid()`
- `has_id(...)`
- `has_email(...)`
- `active()`
- `email_verified()`

## Session model

```cpp
rixlib::auth::Session
```

Fields include:

- id
- user id
- created timestamp
- expiration timestamp
- last seen timestamp
- revoked state

Useful methods:

- `valid()`
- `belongs_to(...)`
- `expired(...)`
- `usable(...)`
- `refreshable(...)`
- `refresh(...)`
- `revoke()`

## Token model

```cpp
rixlib::auth::Token
```

Fields include:

- value
- user id
- issuer
- issued timestamp
- expiration timestamp
- revoked state

Useful methods:

- `valid()`
- `belongs_to(...)`
- `matches(...)`
- `expired(...)`
- `usable(...)`
- `revoke()`

## Testing

Build and run tests with Vix:

```bash
vix tests
```

The test suite covers:

- users
- sessions
- tokens
- password hashing
- memory user store
- memory session store
- auth registration
- login
- logout
- session authentication
- token creation

## Project structure

```text
include/rix/auth/
├── Auth.hpp
├── AuthConfig.hpp
├── AuthError.hpp
├── AuthResult.hpp
├── PasswordHasher.hpp
├── Session.hpp
├── SessionStore.hpp
├── Token.hpp
├── User.hpp
├── UserStore.hpp
├── Version.hpp
└── stores/
    ├── DbSessionStore.hpp
    ├── DbUserStore.hpp
    ├── MemorySessionStore.hpp
    └── MemoryUserStore.hpp

src/
├── Auth.cpp
├── AuthConfig.cpp
├── AuthError.cpp
├── PasswordHasher.cpp
├── Session.cpp
├── SessionStore.cpp
├── Token.cpp
├── User.cpp
├── UserStore.cpp
├── Version.cpp
└── stores/
    ├── DbSessionStore.cpp
    ├── DbUserStore.cpp
    ├── MemorySessionStore.cpp
    └── MemoryUserStore.cpp

tests/
├── AuthTests.cpp
├── MemorySessionStoreTests.cpp
├── MemoryUserStoreTests.cpp
├── PasswordHasherTests.cpp
├── SessionTests.cpp
├── TokenTests.cpp
└── UserTests.cpp

examples/
└── basic.cpp
```

## Security notes

Use `AuthConfig::production()` for real applications.

Do not log:

- plain-text passwords
- password hashes
- session ids
- token values

Use durable database stores when sessions must survive restart.

Use HTTPS when sending sessions or tokens over the network.

Keep password hashing and token generation inside `rix/auth` instead of implementing them in application code.

## Status

Current version:

```cpp
rixlib::auth::version()
```

Current package version:

```text
0.1.0
```

## License

MIT
