#pragma once

#include <cctype>
#include <string>

namespace adizzle {

constexpr auto ltrim(std::string_view str) -> std::string {
    size_t idx = 0;

    while(std::isspace(str.at(idx)) != 0) {
        ++idx;
    }

    return std::string(str.substr(idx, str.size() - idx));
}

constexpr auto rtrim(std::string_view str) -> std::string {
    size_t idx = str.size();

    while(std::isspace(str.at(idx - 1)) != 0) {
        --idx;
    }

    return std::string(str.substr(0, idx));
}

constexpr auto trim(std::string_view str) -> std::string {
    size_t begin_idx = 0;

    while(std::isspace(str.at(begin_idx)) != 0) {
        ++begin_idx;
    }

    str = str.substr(begin_idx, str.size() - begin_idx);

    size_t end_idx = str.size();
    while(std::isspace(str.at(end_idx - 1)) != 0) {
        --end_idx;
    }

    return std::string(str.substr(0, end_idx));
}

} // namespace adizzle