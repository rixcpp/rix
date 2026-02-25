#include <filesystem>
#include <iostream>

#include <rix/io/reader.hpp>

using namespace rix::io;

static int run_example()
{
  const std::filesystem::path missing =
      "/tmp/rix_io_this_file_should_not_exist_123456789.txt";

  const auto txt = try_read_file_text(missing);
  if (!txt)
    std::cout << "[io] try_read_file_text: OK (nullopt for missing file)\n";
  else
    std::cout << "[io] Unexpected: file exists?\n";

  const auto bin = try_read_file_binary(missing);
  if (!bin)
    std::cout << "[io] try_read_file_binary: OK (nullopt for missing file)\n";
  else
    std::cout << "[io] Unexpected: file exists?\n";

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
