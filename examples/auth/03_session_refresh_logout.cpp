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

int main()
{
  rix.debug.print("== rix/auth session refresh and logout ==");

  auto auth = rix.auth.memory();
  auto registered = auth.register_user({"grace@example.com", "correct-password"});

  if (registered.failed())
  {
    const auto &error = registered.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  auto login = auth.login({"grace@example.com", "correct-password"});

  if (login.failed())
  {
    const auto &error = login.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  const auto session_id = login.value().session.id();

  rix.debug.print("created session:", session_id);
  rix.debug.print("expires at:", login.value().session.expires_at());

  auto refreshed = auth.refresh_session(session_id);

  if (refreshed.failed())
  {
    const auto &error = refreshed.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  rix.debug.print("----------------------------------------");
  rix.debug.print("OK:", "session refreshed");
  rix.debug.print("new expires at:", refreshed.value().expires_at());

  auto logout = auth.logout(session_id);

  if (logout.failed())
  {
    const auto &error = logout.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
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
