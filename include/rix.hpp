/**
 * @file rix.hpp
 * @brief Unified Rix facade.
 *
 * This header exposes the global `rix` object.
 *
 * The package `@rix/rix` is the optional unified facade for Rix packages.
 * Individual packages such as `@rix/csv`, `@rix/debug`, and `@rix/auth`
 * stay independent, but this facade mounts them into one object-style API.
 *
 * Example:
 *
 * @code
 * auto table = rix.csv.parse("name,lang\nAda,C++\n");
 * rix.debug.print("loaded rows:", table.size());
 * rix.debug.log("loaded {} rows", table.size());
 *
 * auto auth = rix.auth.memory();
 * auto user = auth.register_user({"ada@example.com", "correct-password"});
 * @endcode
 *
 * @author Gaspard Kirira
 */

#ifndef RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
#define RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED

#include <rix/auth/AuthModule.hpp>
#include <rix/csv.hpp>
#include <rix/debug.hpp>

namespace rixlib
{
  /**
   * @brief Unified Rix API facade.
   *
   * This class groups independent Rix components into one object.
   */
  class Rix
  {
  public:
    /**
     * @brief CSV reader and writer component.
     */
    rixlib::csv::Csv csv{};

    /**
     * @brief Debug printing, formatting, logging, and inspection component.
     */
    rixlib::debug::Debug debug{};

    /**
     * @brief Authentication component.
     */
    rixlib::auth::AuthModule auth{};
  };
}

/**
 * @brief Global Rix facade object.
 *
 * This object allows API usage such as:
 *
 * @code
 * rix.csv.parse(...)
 * rix.debug.print(...)
 * rix.debug.format(...)
 * rix.debug.log(...)
 * rix.debug.inspect(...)
 * rix.auth.memory()
 * rix.auth.database(db)
 * rix.auth.create(users, sessions)
 * rix.auth.password.hash(...)
 * rix.auth.config.production()
 * @endcode
 */
inline constexpr rixlib::Rix rix{};

#endif // RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
