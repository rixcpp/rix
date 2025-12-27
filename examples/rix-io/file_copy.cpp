#include <cassert>
#include <filesystem>
#include <iostream>
#include <span>
#include <string>
#include <vector>

#include "rix/io/reader.hpp"
#include "rix/io/util.hpp"
#include "rix/io/writer.hpp"

using namespace rix::io;

static int run_example()
{
    const auto src = temp_path("rix_io_copy_src");
    const auto dst = temp_path("rix_io_copy_dst");

    std::cout << "[rix-io] src: " << src << "\n";
    std::cout << "[rix-io] dst: " << dst << "\n";

    const std::string content =
        "Rix IO copy example\n"
        "This file will be copied as bytes.\n";

    write_file_text(src, content);

    const std::vector<std::byte> bytes = read_file_binary(src);
    write_file_binary(dst, std::span<const std::byte>(bytes.data(), bytes.size()));

    const auto out = read_file_text(dst);
    assert(out == content);

    std::cout << "[rix-io] Copy OK\n";

    std::error_code ec;
    std::filesystem::remove(src, ec);
    std::filesystem::remove(dst, ec);
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
