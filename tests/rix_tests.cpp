/**
 * @file rix_tests.cpp
 * @brief Basic tests for the Rix facade.
 */

#include <rix.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
  void expect_true(bool condition, const std::string &message)
  {
    if (!condition)
    {
      std::cerr << "FAILED: " << message << '\n';
      std::exit(1);
    }
  }

  void test_global_rix_csv_parse()
  {
    const std::string input =
        "name,language\n"
        "Ada,C++\n";

    const auto table = rix.csv.parse(input);

    expect_true(table.size() == 2, "rix.csv.parse should return 2 rows");
    expect_true(table[0][0] == "name", "header first field should be name");
    expect_true(table[1][0] == "Ada", "data first field should be Ada");
    expect_true(table[1][1] == "C++", "data second field should be C++");
  }

  void test_global_rix_csv_write()
  {
    const rixlib::csv::Table table = {
        {"name", "language"},
        {"Ada", "C++"},
    };

    const std::string output = rix.csv.write(table);

    const std::string expected =
        "name,language\n"
        "Ada,C++\n";

    expect_true(output == expected, "rix.csv.write should serialize CSV data");
  }

  void run_tests()
  {
    test_global_rix_csv_parse();
    test_global_rix_csv_write();
  }
}

int main()
{
  run_tests();

  std::cout << "rix tests passed\n";
  return 0;
}
