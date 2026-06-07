/**
 * @file csv.cpp
 * @brief CSV example for the unified Rix facade.
 */

#include <rix.hpp>

#include <sstream>
#include <string>

namespace
{
  void print_table(const rixlib::csv::Table &table)
  {
    for (const auto &row : table)
    {
      std::ostringstream line;

      for (std::size_t i = 0; i < row.size(); ++i)
      {
        if (i > 0)
        {
          line << " ";
        }

        line << row[i];
      }

      rix.debug.print(line.str());
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
