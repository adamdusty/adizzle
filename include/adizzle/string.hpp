#pragma once

#include <cctype>
#include <string>
#include <vector>

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

constexpr auto split(const std::string& str, char delim) -> std::vector<std::string> {
    auto results = std::vector<std::string>();

    size_t index = 0;
    auto current = std::string();
    while(index < str.size()) {
        if(str.at(index) == delim) {
            results.emplace_back(current);
            current = std::string();
            ++index;
            continue;
        }

        current += str.at(index++);
    }

    results.emplace_back(current);

    return results;
}

} // namespace adizzle