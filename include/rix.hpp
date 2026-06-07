/**
 * @file rix.hpp
 * @brief Unified Rix facade.
 *
 * This header exposes the global `rix` object.
 *
 * The package `@rix/rix` is the optional unified facade for Rix packages.
 * Individual packages such as `@rix/csv` stay independent, but this facade
 * mounts them into one object-style API.
 *
 * Example:
 *
 * @code
 * auto table = rix.csv.parse("name,lang\nAda,C++\n");
 * @endcode
 *
 * @author Gaspard Kirira
 */

#ifndef RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
#define RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED

#include <rix/csv.hpp>

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
  };
}

/**
 * @brief Global Rix facade object.
 *
 * This object allows API usage such as:
 *
 * @code
 * rix.csv.parse(...)
 * @endcode
 */
inline constexpr rixlib::Rix rix{};

#endif // RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
