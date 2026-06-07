/**
 * @file basic.cpp
 * @brief Basic example for the Rix facade.
 */

#include <rix.hpp>

#include <iostream>
#include <string>

namespace
{
  void run_basic_example()
  {
    const std::string input =
        "name,language\n"
        "Ada,C++\n"
        "Gaspard,Vix\n";

    const auto table = rix.csv.parse(input);

    for (const auto &row : table)
    {
      for (const auto &field : row)
      {
        std::cout << field << ' ';
      }

      std::cout << '\n';
    }
  }
}

int main()
{
  run_basic_example();
  return 0;
}
