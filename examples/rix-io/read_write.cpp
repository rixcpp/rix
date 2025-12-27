#include <filesystem>
#include <iostream>
#include <string>

#include "rix/io/reader.hpp"
#include "rix/io/util.hpp"
#include "rix/io/writer.hpp"

using namespace rix::io;

static int run_example()
{
    const auto path = temp_path("rix_io_example");

    std::cout << "[rix-io] Example file: " << path << "\n";

    const std::string content =
        "Rix IO example\n"
        "--------------\n"
        "This file was created by rix::io.\n";

    write_file_text(path, content);

    const auto loaded = read_file_text(path);

    std::cout << "[rix-io] Loaded content:\n";
    std::cout << "------------------------\n";
    std::cout << loaded << "\n";

    // cleanup best-effort
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
        std::cerr << "[rix-io] Example failed: " << ex.what() << "\n";
        return 1;
    }
}
