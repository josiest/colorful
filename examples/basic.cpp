#include <colorful/colorful.hpp>
#include <cstdint>
#include <iostream>
#include <iomanip>

struct color { std::uint8_t r, g, b, a; };
namespace cf = colorful;

int main()
{
    auto white = cf::color_from_hex<color>(0xffffff);
    std::cout << std::hex
              << "white: {" << +white.r << ", " << +white.g << ", "
                            << +white.b << ", " << +white.a << "}"
              << std::endl;
}
