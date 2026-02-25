#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

#include <rix/io/reader.hpp>
#include <rix/io/util.hpp>
#include <rix/io/writer.hpp>

using namespace rix::io;

static int run_example()
{
  const auto path = temp_path("io_append");

  std::cout << "[io] File: " << path << "\n";

  write_file_text(path, "Line A\n", WriteMode::append);
  write_file_text(path, "Line B\n", WriteMode::append);
  write_file_text(path, "Line C\n", WriteMode::append);

  const auto loaded = read_file_text(path);

  std::cout << "[io] Loaded:\n";
  std::cout << "----------------\n";
  std::cout << loaded;

  std::error_code ec;
  std::filesystem::remove(path, ec);
  return 0;
}

int main()
{
  try
  {
    return run_example();
  }
  catch (const std::exception &ex)
  {
    std::cerr << "[io] Example failed: " << ex.what() << "\n";
    return 1;
  }
}
