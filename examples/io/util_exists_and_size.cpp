#include <filesystem>
#include <iostream>

#include <rix/io/util.hpp>
#include <rix/io/writer.hpp>

static int run_example()
{
  const auto path = rix::io::temp_path("rix_io_size");

  std::cout << "[io] Path: " << path << "\n";
  std::cout << "[io] exists(before) = " << (rix::io::path_exists(path) ? "true" : "false") << "\n";

  rix::io::write_file_text(path, "1234567890\n");

  std::cout << "[io] exists(after)  = " << (rix::io::path_exists(path) ? "true" : "false") << "\n";
  std::cout << "[io] path_size      = " << rix::io::path_size(path) << " bytes\n";

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
