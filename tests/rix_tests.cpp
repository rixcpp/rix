/**
 * @file rix_tests.cpp
 * @brief Basic tests for the unified Rix facade.
 *
 * @author Gaspard Kirira
 */

#include <rix.hpp>

#include <cstdlib>
#include <iostream>
#include <sstream>
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
    expect_true(table[0][1] == "language", "header second field should be language");
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

  void test_global_rix_debug_format()
  {
    const std::string output = rix.debug.format("Hello {}", "Rix");

    expect_true(
        output == "Hello Rix",
        "rix.debug.format should format automatic placeholders");
  }

  void test_global_rix_debug_format_explicit_indexes()
  {
    const std::string output = rix.debug.format("{0} + {0} = {1}", 2, 4);

    expect_true(
        output == "2 + 2 = 4",
        "rix.debug.format should format explicit placeholders");
  }

  void test_global_rix_debug_format_escaped_braces()
  {
    const std::string output = rix.debug.format("{{ value }} = {}", 42);

    expect_true(
        output == "{ value } = 42",
        "rix.debug.format should support escaped braces");
  }

  void test_global_rix_debug_format_append()
  {
    std::string output = "prefix: ";

    rix.debug.format.append(output, "{}", "ready");

    expect_true(
        output == "prefix: ready",
        "rix.debug.format.append should append formatted text");
  }

  void test_global_rix_debug_format_to()
  {
    std::string output = "old";

    rix.debug.format.to(output, "status: {}", "ok");

    expect_true(
        output == "status: ok",
        "rix.debug.format.to should replace destination content");
  }

  void test_global_rix_debug_print_to_stream()
  {
    std::ostringstream out;

    rixlib::print_to(out, "Hello", "Rix");

    expect_true(
        out.str() == "Hello Rix\n",
        "rixlib::print_to should write arguments separated by spaces with newline");
  }

  void test_global_rix_debug_inspect_to_string()
  {
    expect_true(
        rix.debug.inspect.to_string(42) == "42",
        "rix.debug.inspect.to_string should inspect integers");

    expect_true(
        rix.debug.inspect.to_string(true) == "true",
        "rix.debug.inspect.to_string should inspect booleans");
  }

  void test_global_rix_debug_inspect_check_pass()
  {
    const bool ok = rix.debug.inspect.check(42, 42);

    expect_true(
        ok,
        "rix.debug.inspect.check should return true when values are equal");
  }

  void test_global_rix_debug_inspect_check_fail()
  {
    const bool ok = rix.debug.inspect.check(42, 24);

    expect_true(
        !ok,
        "rix.debug.inspect.check should return false when values are different");
  }

  void run_tests()
  {
    test_global_rix_csv_parse();
    test_global_rix_csv_write();

    test_global_rix_debug_format();
    test_global_rix_debug_format_explicit_indexes();
    test_global_rix_debug_format_escaped_braces();
    test_global_rix_debug_format_append();
    test_global_rix_debug_format_to();
    test_global_rix_debug_print_to_stream();
    test_global_rix_debug_inspect_to_string();
    test_global_rix_debug_inspect_check_pass();
    test_global_rix_debug_inspect_check_fail();
  }
}

int main()
{
  run_tests();

  std::cout << "rix facade tests passed\n";
  return 0;
}
