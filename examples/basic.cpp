/**
 * @file basic.cpp
 * @brief Basic example for the unified Rix facade.
 */

#include <rix.hpp>

int main()
{
  rix.debug.print("Hello {}", "Rix");
  rix.debug.log("facade is ready");

  return 0;
}
