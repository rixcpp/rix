/**
 *
 *  @file 02_password_hash.cpp
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
    rix.debug.print("== rix/auth password hashing ==");

    const auto password = "correct-password";

    auto hashed = rix.auth.password.hash(password);

    if (hashed.failed())
    {
      print_auth_error(hashed.error());
      return 1;
    }

    const bool valid = rix.auth.password.verify(
        password,
        hashed.value());

    const bool invalid = rix.auth.password.verify(
        "wrong-password",
        hashed.value());

    rix.debug.print("hash:", hashed.value());
    rix.debug.print("valid password:", valid ? "yes" : "no");
    rix.debug.print("wrong password:", invalid ? "yes" : "no");

    if (!valid || invalid)
    {
      rix.debug.eprint("ERROR:", "password verification failed");
      return 1;
    }

    rix.debug.print("OK:", "password verification successful");
    return 0;
  }
} // namespace

int main()
{
  return run_example();
}
