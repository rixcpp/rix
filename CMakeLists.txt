cmake_minimum_required(VERSION 3.20)

# ====================================================================
# Rix - Minimal Modern C++ Utility Library
# --------------------------------------------------------------------
# Top-level umbrella CMake configuration for all modules.
#
# Rix is a small, modular collection of modern C++20 utilities designed
# to feel like a lightweight "essential standard library":
#
#   - io        : file and stream helpers
#   - string    : string utilities
#   - memory    : memory helpers and smart wrappers
#   - containers: minimal container helpers
#   - json      : JSON encoding/decoding
#   - net       : basic networking primitives
#   - fs        : filesystem helpers
#   - thread    : threading helpers
#   - log       : logging utilities
#   - assert    : assertion helpers
#   - util      : common utility helpers
#   - process   : process and system helpers
#   - iterator  : iterator helpers
#   - chrono    : time and duration helpers
#   - async     : async primitives
#
# This CMake file:
#   - defines global build settings for Rix
#   - exposes options to enable/disable individual modules
#   - wires each module via add_subdirectory(...)
#   - collects enabled module targets into a single aggregate target:
#         rix::all
#   - installs a single CMake package config (rixConfig.cmake) that
#     exposes all installed rix::* targets.
#
# Typical consumer usage:
#
#   find_package(rix REQUIRED)
#
#   target_link_libraries(my_app PRIVATE rix::io)     # single module
#   target_link_libraries(my_app PRIVATE rix::all)    # all enabled modules
#
# ====================================================================

project(rix VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ====================================================================
# Global compiler settings
# ====================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Global warning flags (can be tuned by consumers if needed).
set(RIX_GLOBAL_CXX_FLAGS "-Wall -Wextra -Wshadow")

set(CMAKE_CXX_FLAGS_RELEASE "${RIX_GLOBAL_CXX_FLAGS} -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "${RIX_GLOBAL_CXX_FLAGS} -g")

# ====================================================================
# Umbrella module options
# ====================================================================
# These options control which modules are built as part of this
# umbrella project. Only io is enabled by default for now.
#
# Each module is expected to:
#   - live under modules/<name>
#   - define a target named rix::<name>
#   - install itself into the shared export set "RixTargets".
# ====================================================================

option(RIX_ENABLE_IO          "Build io module"          ON)
option(RIX_ENABLE_STRING      "Build string module"      OFF)
option(RIX_ENABLE_MEMORY      "Build memory module"      OFF)
option(RIX_ENABLE_CONTAINERS  "Build containers module"  OFF)
option(RIX_ENABLE_JSON        "Build json module"        OFF)
option(RIX_ENABLE_NET         "Build net module"         OFF)
option(RIX_ENABLE_FS          "Build fs module"          OFF)
option(RIX_ENABLE_THREAD      "Build thread module"      OFF)
option(RIX_ENABLE_LOG         "Build log module"         OFF)
option(RIX_ENABLE_ASSERT      "Build assert module"      OFF)
option(RIX_ENABLE_UTIL        "Build util module"        OFF)
option(RIX_ENABLE_PROCESS     "Build process module"     OFF)
option(RIX_ENABLE_ITERATOR    "Build iterator module"    OFF)
option(RIX_ENABLE_CHRONO      "Build chrono module"      OFF)
option(RIX_ENABLE_ASYNC       "Build async module"       OFF)

# Global knobs to control tests and examples for all modules that support them.
option(RIX_ENABLE_TESTS       "Enable tests in all rix modules (where supported)"     ON)
option(RIX_ENABLE_EXAMPLES    "Enable examples in all rix modules (where supported)" ON)

# ====================================================================
# Sanitizers (umbrella-level)
# ====================================================================
# When enabled, modules that support sanitizers should opt-in to
# address/UB sanitizers for their library, tests, and examples.
# Each module decides how it applies these flags.
# ====================================================================

option(RIX_ENABLE_SANITIZERS  "Enable sanitizers for all rix modules (where supported)" OFF)

# For now, only io uses module-specific options:
#   - RIX_IO_BUILD_TESTS
#   - RIX_IO_BUILD_EXAMPLES
#   - RIX_IO_ENABLE_SANITIZERS
if (RIX_ENABLE_IO)
  set(RIX_IO_BUILD_TESTS        ${RIX_ENABLE_TESTS}       CACHE BOOL "Build io tests"         FORCE)
  set(RIX_IO_BUILD_EXAMPLES     ${RIX_ENABLE_EXAMPLES}    CACHE BOOL "Build io examples"      FORCE)
  set(RIX_IO_ENABLE_SANITIZERS  ${RIX_ENABLE_SANITIZERS}  CACHE BOOL "Enable sanitizers in io" FORCE)
endif()

# ====================================================================
# Modules
# ====================================================================
# As modules are added, they should:
#   - be guarded by their RIX_ENABLE_<NAME> option
#   - add_subdirectory(modules/<name>)
#   - append their rix::<name> target to RIX_ENABLED_MODULE_TARGETS
# ====================================================================

set(RIX_ENABLED_MODULE_TARGETS "")

# ------------- io ----------------------------------------------------
if (RIX_ENABLE_IO)
  add_subdirectory(modules/io)

  # io is expected to define the target rix::io
  if (TARGET rix::io)
    list(APPEND RIX_ENABLED_MODULE_TARGETS rix::io)
  endif()
endif()

# ------------- Other modules (pattern / TODO) ------------------------
#
# Example pattern to follow when wiring new modules:
#
# if (RIX_ENABLE_STRING)
#   add_subdirectory(modules/string)
#   if (TARGET rix::string)
#     list(APPEND RIX_ENABLED_MODULE_TARGETS rix::string)
#   endif()
# endif()
#
# if (RIX_ENABLE_JSON)
#   add_subdirectory(modules/json)
#   if (TARGET rix::json)
#     list(APPEND RIX_ENABLED_MODULE_TARGETS rix::json)
#   endif()
# endif()
#
# ...and so on for each module.
#
# --------------------------------------------------------------------

# ====================================================================
# Aggregate target: rix::all
# ====================================================================
# rix::all is a convenience INTERFACE target that links all enabled
# module targets together. Consumers can simply link against rix::all
# instead of each module individually.
# ====================================================================

if (RIX_ENABLED_MODULE_TARGETS)
  add_library(rix_all INTERFACE)
  add_library(rix::all ALIAS rix_all)

  target_link_libraries(rix_all
    INTERFACE
      ${RIX_ENABLED_MODULE_TARGETS}
  )
endif()

# ====================================================================
# Installation & CMake package configuration
# ====================================================================
# All modules should install their targets into the shared export set
# "RixTargets":
#
#   install(TARGETS <module-target>
#           EXPORT RixTargets
#           ...)
#
# This umbrella CMakeLists then installs that export set and generates
# a single package config so that consumers can use:
#
#   find_package(rix REQUIRED)
#
# ====================================================================

install(
  EXPORT RixTargets
  NAMESPACE rix::
  FILE RixTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rix
)

# Directory where rixConfig.cmake and rixConfigVersion.cmake will be installed.
set(RIX_CMAKE_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/rix")

# Configure rixConfig.cmake from cmake/rixConfig.cmake.in
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rixConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/rixConfig.cmake
  INSTALL_DESTINATION ${RIX_CMAKE_CONFIG_DIR}
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/rixConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/rixConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/rixConfigVersion.cmake
  DESTINATION ${RIX_CMAKE_CONFIG_DIR}
)

# Note:
#   - Headers for each module are installed by the module itself
#     (e.g. io installs include/rix/io/*.hpp).
#   - If an umbrella header (e.g. <rix/rix.hpp>) is added later, it
#     should be installed here at the top level.

# ====================================================================
# Summary
# ====================================================================

message(STATUS "======================================================")
message(STATUS "Rix umbrella configured (${PROJECT_VERSION})")
message(STATUS "Install prefix       : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMake config dir     : ${RIX_CMAKE_CONFIG_DIR}")
message(STATUS "Enabled modules      : ${RIX_ENABLED_MODULE_TARGETS}")
message(STATUS "Tests enabled        : ${RIX_ENABLE_TESTS}")
message(STATUS "Examples enabled     : ${RIX_ENABLE_EXAMPLES}")
message(STATUS "Sanitizers enabled   : ${RIX_ENABLE_SANITIZERS}")
message(STATUS "======================================================")
