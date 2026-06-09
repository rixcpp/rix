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

namespace
{
  void print_auth_error(const rixlib::auth::AuthError &error)
  {
    rix.debug.eprint("auth error:", rixlib::auth::to_string(error.code()), error.message());
  }

  int run_example()
  {
    rix.debug.print("== rix/auth token issue ==");

    auto auth = rix.auth.memory();
    auto registered = auth.register_user(rixlib::auth::RegisterRequest{"linus@example.com", "correct-password"});

    if (registered.failed())
    {
      print_auth_error(registered.error());
      return 1;
    }

    auto token = auth.issue_token(registered.value().id());

    if (token.failed())
    {
      print_auth_error(token.error());
      return 1;
    }

    rix.debug.print("OK:", "token issued");
    rix.debug.print("user id:", token.value().user_id());
    rix.debug.print("issuer:", token.value().issuer());
    rix.debug.print("issued at:", token.value().issued_at());
    rix.debug.print("expires at:", token.value().expires_at());

    return 0;
  }
} // namespace

int main()
{
  return run_example();
}
