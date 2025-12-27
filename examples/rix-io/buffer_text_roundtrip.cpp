#include <cassert>
#include <exception>
#include <iostream>
#include <string>

#include "rix/io/buffer.hpp"

using namespace rix::io;

static int run_example()
{
    const std::string text = "Hello from rix::io::Buffer ✅\nLine2\n";

    Buffer buf(text);
    assert(buf.size() == text.size());
    assert(!buf.empty());

    const std::string out = buf.to_string();
    assert(out == text);

    std::cout << "[rix-io] Buffer roundtrip OK\n";
    std::cout << out;
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
