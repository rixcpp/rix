#include <cassert>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <iostream>
#include <span>
#include <vector>

#include "rix/io/reader.hpp"
#include "rix/io/util.hpp"
#include "rix/io/writer.hpp"

using namespace rix::io;

static std::vector<std::byte> make_bytes()
{
    std::vector<std::byte> out;
    out.reserve(16);

    for (int i = 0; i < 16; ++i)
        out.push_back(static_cast<std::byte>(i));

    return out;
}

static int run_example()
{
    const auto path = temp_path("rix_io_bin");

    std::cout << "[rix-io] Binary file: " << path << "\n";

    const auto bytes = make_bytes();
    write_file_binary(path, std::span<const std::byte>(bytes.data(), bytes.size()));

    const auto loaded = read_file_binary(path);

    assert(loaded.size() == bytes.size());
    for (std::size_t i = 0; i < bytes.size(); ++i)
        assert(loaded[i] == bytes[i]);

    std::cout << "[rix-io] OK: read_file_binary == written bytes (" << loaded.size() << " bytes)\n";

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
