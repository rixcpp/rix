/**
 * @file debug.cpp
 * @brief Debug example for the unified Rix facade.
 */

#include <rix.hpp>

int main()
{
  rix.debug.print("Hello", "Rix");

  const std::string package = rix.debug.format("Package: {}", "rix/rix");

  rix.debug.print(package);
  rix.debug.log("loaded {} debug APIs", 4);
  rix.debug.log.warn("this is a warning: {}", "slow path");
  rix.debug.inspect(package);

  return 0;
}
