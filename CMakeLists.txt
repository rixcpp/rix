cmake_minimum_required(VERSION 3.20)

project(rix
  VERSION 0.5.0
  DESCRIPTION "Unified Rix facade for Vix C++ projects"
  LANGUAGES CXX
)

option(RIX_BUILD_EXAMPLES "Build Rix examples" ON)
option(RIX_BUILD_TESTS "Build Rix tests" ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake OPTIONAL)

add_library(rix INTERFACE)
add_library(rix::rix ALIAS rix)

target_compile_features(rix
  INTERFACE
    cxx_std_20
)

target_include_directories(rix
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(rix
  INTERFACE
    rix::csv
    rix::debug
    rix::auth
    rix::pdf
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  if(RIX_BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()

  if(RIX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()
endif()
