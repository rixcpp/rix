/**
 *
 *  @file 01_memory_register_login.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/rixcpp/rix
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Rix
 *
 */

#include <rix.hpp>

int main()
{
  rix.debug.print("== rix/auth memory register and login ==");

  auto auth = rix.auth.memory();
  auto registered = auth.register_user({"ada@example.com", "correct-password"});

  if (registered.failed())
  {
    const auto &error = registered.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  rix.debug.print("registered user");
  rix.debug.print("id:", registered.value().id());
  rix.debug.print("email:", registered.value().email());

  auto login = auth.login({"ada@example.com", "correct-password"});

  if (login.failed())
  {
    const auto &error = login.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  rix.debug.print("----------------------------------------");
  rix.debug.print("login successful");
  rix.debug.print("user:", login.value().user.email());
  rix.debug.print("session:", login.value().session.id());
  rix.debug.print("token issuer:", login.value().token.issuer());

  auto session = auth.authenticate_session(login.value().session.id());

  if (session.failed())
  {
    const auto &error = session.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  rix.debug.print("----------------------------------------");
  rix.debug.print("OK:", "session authenticated");
  rix.debug.print("session user id:", session.value().user_id());

  return 0;
}
