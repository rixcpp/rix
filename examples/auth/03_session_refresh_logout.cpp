/**
 *
 *  @file 03_session_refresh_logout.cpp
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
    rix.debug.print("== rix/auth session refresh and logout ==");

    auto auth = rix.auth.memory();

    auto registered = auth.register_user(
        rixlib::auth::RegisterRequest{
            "grace@example.com",
            "correct-password"});

    if (registered.failed())
    {
      print_auth_error(registered.error());
      return 1;
    }

    auto login = auth.login(
        rixlib::auth::LoginRequest{
            "grace@example.com",
            "correct-password"});

    if (login.failed())
    {
      print_auth_error(login.error());
      return 1;
    }

    const auto session_id = login.value().session.id();

    rix.debug.print("created session:", session_id);
    rix.debug.print("expires at:", login.value().session.expires_at());

    auto refreshed = auth.refresh_session(session_id);

    if (refreshed.failed())
    {
      print_auth_error(refreshed.error());
      return 1;
    }

    rix.debug.print("----------------------------------------");
    rix.debug.print("OK:", "session refreshed");
    rix.debug.print("new expires at:", refreshed.value().expires_at());

    auto logout = auth.logout(session_id);

    if (logout.failed())
    {
      print_auth_error(logout.error());
      return 1;
    }

    rix.debug.print("----------------------------------------");
    rix.debug.print("OK:", "logout successful");

    auto after_logout = auth.authenticate_session(session_id);

    if (after_logout.ok())
    {
      rix.debug.eprint("ERROR:", "session should not be valid after logout");
      return 1;
    }

    rix.debug.print("session rejected after logout");
    return 0;
  }
} // namespace

int main()
{
  return run_example();
}
