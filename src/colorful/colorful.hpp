#pragma once

// data types
#include <string>

// data structures and resource handlers
#include <unordered_map>
#include <tl/expected.hpp>

// i/o
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace colorful {

using namespace std::string_literals;

template<class Color>
concept color = requires(int v) {
    Color(v, v, v, v);
};

template<color Color>
using color_table = std::unordered_map<std::string, Color>;

/** Parse a Color object from a hex value.
 *
 * \param hex the color value to parse
 *
 * Each 8 bits should represent an 8-bit color value. The values should be order
 * of rgb, where blue is the least significant eight bits.
 */
template<color Color>
constexpr Color color_from_hex(int hex)
{
    return Color(
        (hex >> 16) & 0xff, // red value
        (hex >> 8) & 0xff,  // green value
        hex & 0xff,         // blue value
        0xff                // alpha value
    );
}

/** Load a color table from a file.
 *
 * \param path the path to the color config file.
 * \return a color table of the colors defined in the file.
 *
 * The color specification should resemble a yaml mapping of the color name to
 * the hex value it takes. For example:
 *
 *   white:ffffff
 *   light-blue:3399ff
 *   ...
 *
 * Each color definition will be loaded as a string-color pair into a color
 * table.
 */
template<color Color>
tl::expected<color_table<Color>, std::string>
load_table(std::filesystem::path const & path)
{
    // use error codes so as not to throw exceptions
    std::error_code ec;

    // make sure the file is valid
    bool const file_exists = std::filesystem::exists(path, ec);
    bool const file_is_valid = std::filesystem::is_regular_file(path, ec);

    // return an error if the file given isn't valid
    if (ec) {
        return tl::unexpected("an os call failed: "s + ec.message());
    }
    else if (not file_exists) {
        return tl::unexpected(path.string() + " doesn't exist"s);
    }
    else if (not file_is_valid) {
        return tl::unexpected(path.string() + " isn't a file"s);
    }

    // load the file
    std::ifstream config(path, config.in);

    // error if couldn't open the file
    if (not config.is_open()) {
        return tl::unexpected("coudln't open "s + path.string());
    }

    color_table<Color> colors;

    // read each line
    std::string line;
    while (std::getline(config, line)) {
        std::istringstream line_stream(line);
        std::string name, hexstr;

        // split by colon
        if (not std::getline(line_stream, name, ':')) {
            return tl::unexpected("encountered an i/o error"s);
        }
        if (not std::getline(line_stream, hexstr)) {
            return tl::unexpected("encountered an i/o error"s);
        }

        // parse the hex value
        char * end;
        errno = 0;
        long const value = std::strtol(hexstr.c_str(), &end, 16);

        // value must be in range
        long const color_max = 16777215;
        if (value < 0 or value > color_max) {
            return tl::unexpected("color values must be between 0 and 255 (inclusive)"s);
        }
        // value must be an int
        else if (hexstr == "\0" or *end != '\0') {
            return tl::unexpected("color value given is non-integer"s);
        }

        // and add it to the color table
        colors.insert_or_assign(name, color_from_hex<Color>(value));
    }
    return colors;
}
}
