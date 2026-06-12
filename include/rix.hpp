/**
 * @file rix.hpp
 * @brief Unified Rix facade.
 *
 * This header exposes the global `rix` object.
 *
 * By default, it keeps the historical behavior and enables all available
 * mounted Rix packages.
 *
 * For lighter builds, define only the packages you want before including
 * this header:
 *
 * @code
 * #define RIX_ENABLE_CSV
 * #include <rix.hpp>
 *
 * auto table = rix.csv.parse("name,lang\nAda,C++\n");
 * @endcode
 *
 * Available feature macros:
 *
 * - RIX_ENABLE_CSV
 * - RIX_ENABLE_DEBUG
 * - RIX_ENABLE_AUTH
 * - RIX_ENABLE_PDF
 *
 * To keep backward compatibility, if no RIX_ENABLE_* macro is defined,
 * all current facade modules are enabled.
 *
 * @author Gaspard Kirira
 */

#ifndef RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
#define RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED

/*
 * Backward compatibility mode.
 *
 * Existing code that does:
 *
 *   #include <rix.hpp>
 *
 * should keep working exactly as before.
 *
 * If the user defines at least one RIX_ENABLE_* macro, only those selected
 * modules are mounted into the facade.
 */
#if !defined(RIX_ENABLE_CSV) &&   \
    !defined(RIX_ENABLE_DEBUG) && \
    !defined(RIX_ENABLE_AUTH) &&  \
    !defined(RIX_ENABLE_PDF)

#define RIX_ENABLE_CSV
#define RIX_ENABLE_DEBUG
#define RIX_ENABLE_AUTH
#define RIX_ENABLE_PDF

#endif

#ifdef RIX_ENABLE_CSV
#include <rix/csv.hpp>
#endif

#ifdef RIX_ENABLE_DEBUG
#include <rix/debug.hpp>
#endif

#ifdef RIX_ENABLE_AUTH
#include <rix/auth/AuthModule.hpp>
#endif

#ifdef RIX_ENABLE_PDF
#include <rix/pdf/PdfModule.hpp>
#endif

namespace rixlib
{
  /**
   * @brief Unified Rix API facade.
   *
   * This class groups selected independent Rix components into one object.
   *
   * The mounted components depend on the RIX_ENABLE_* macros defined before
   * including <rix.hpp>.
   */
  class Rix
  {
  public:
#ifdef RIX_ENABLE_CSV
    /**
     * @brief CSV reader and writer component.
     */
    rixlib::csv::Csv csv{};
#endif

#ifdef RIX_ENABLE_DEBUG
    /**
     * @brief Debug printing, formatting, logging, and inspection component.
     */
    rixlib::debug::Debug debug{};
#endif

#ifdef RIX_ENABLE_AUTH
    /**
     * @brief Authentication component.
     */
    rixlib::auth::AuthModule auth{};
#endif

#ifdef RIX_ENABLE_PDF
    /**
     * @brief PDF generation and document utilities component.
     */
    rixlib::pdf::PdfModule pdf{};
#endif
  };
}

/**
 * @brief Global Rix facade object.
 *
 * Default usage:
 *
 * @code
 * #include <rix.hpp>
 *
 * rix.csv.parse(...);
 * rix.debug.print(...);
 * rix.auth.memory();
 * rix.pdf.document();
 * @endcode
 *
 * Lightweight usage:
 *
 * @code
 * #define RIX_ENABLE_CSV
 * #include <rix.hpp>
 *
 * rix.csv.parse(...);
 * @endcode
 */
inline constexpr rixlib::Rix rix{};

#endif // RIXCPP_RIX_INCLUDE_RIX_HPP_INCLUDED
