#include <colorful/colorful.hpp>

// data types
#include <cstdint>

// i/o
#include <iostream>
#include <iomanip>
#include <filesystem>

struct color { int r, g, b, a; };
namespace cf = colorful;
namespace fs = std::filesystem;

namespace std {
ostream & operator<<(ostream & os, color const & c)
{
    os << hex << "{" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << "}";
    return os;
}
}

int main()
{
    auto white = cf::color_from_hex<color>(0xffffff);
    std::cout << "white: " << white << std::endl;

    fs::path const color_path = fs::absolute("../colors.yaml");
    auto colors = cf::load_table<color>(color_path);
    if (not colors) {
        std::cout << "unable to load colors: " << colors.error() << std::endl;
        return EXIT_FAILURE;
    }

    for (auto const &[name, color] : *colors) {
        std::cout << name << ": " << color << std::endl;
    }
    return EXIT_SUCCESS;
}
