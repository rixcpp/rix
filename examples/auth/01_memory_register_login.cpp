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

namespace
{
  void print_auth_error(const rixlib::auth::AuthError &error)
  {
    rix.debug.eprint(
        "auth error:",
        rixlib::auth::to_string(error.code()),
        error.message());
  }

  int run_example()
  {
    rix.debug.print("== rix/auth memory register and login ==");

    auto auth = rix.auth.memory();

    auto registered = auth.register_user(
        rixlib::auth::RegisterRequest{
            "ada@example.com",
            "correct-password"});

    if (registered.failed())
    {
      print_auth_error(registered.error());
      return 1;
    }

    rix.debug.print("registered user");
    rix.debug.print("id:", registered.value().id());
    rix.debug.print("email:", registered.value().email());

    auto login = auth.login(
        rixlib::auth::LoginRequest{
            "ada@example.com",
            "correct-password"});

    if (login.failed())
    {
      print_auth_error(login.error());
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
      print_auth_error(session.error());
      return 1;
    }

    rix.debug.print("----------------------------------------");
    rix.debug.print("OK:", "session authenticated");
    rix.debug.print("session user id:", session.value().user_id());

    return 0;
  }
} // namespace

int main()
{
  return run_example();
}
