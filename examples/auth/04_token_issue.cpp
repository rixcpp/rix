/**
 *
 *  @file 04_token_issue.cpp
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
  rix.debug.print("== rix/auth token issue ==");

  auto auth = rix.auth.memory();
  auto registered = auth.register_user({"linus@example.com", "correct-password"});

  if (registered.failed())
  {
    const auto &error = registered.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  auto token = auth.issue_token(registered.value().id());

  if (token.failed())
  {
    const auto &error = token.error();
    rix.debug.eprint("auth error:", rix.auth.error.to_string(error), error.message());
    return 1;
  }

  rix.debug.print("OK:", "token issued");
  rix.debug.print("user id:", token.value().user_id());
  rix.debug.print("issuer:", token.value().issuer());
  rix.debug.print("issued at:", token.value().issued_at());
  rix.debug.print("expires at:", token.value().expires_at());

  return 0;
}
