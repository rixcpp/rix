/**
 * @file csv.cpp
 * @brief CSV example for the unified Rix facade.
 */

#include <rix.hpp>

#include <string>

namespace
{
  void print_table(const rixlib::csv::Table &table)
  {
    for (const auto &row : table)
    {
      for (const auto &field : row)
      {
        rix.debug.print.inline_text("{} ", field);
      }

      rix.debug.print();
    }
  }
}

int main()
{
  const std::string input =
      "name,language\n"
      "Ada,C++\n"
      "Gaspard,Vix\n";

  const auto table = rix.csv.parse(input);

  rix.debug.log("loaded {} rows", table.size());
  print_table(table);

  return 0;
}
