#pragma once

#include <cctype>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace adizzle {

inline auto ltrim(std::string_view str) -> std::string {
    size_t idx = 0;

    while(std::isspace(str.at(idx)) != 0) {
        ++idx;
    }

    return std::string(str.substr(idx, str.size() - idx));
}

inline auto rtrim(std::string_view str) -> std::string {
    size_t idx = str.size();

    while(std::isspace(str.at(idx - 1)) != 0) {
        --idx;
    }

    return std::string(str.substr(0, idx));
}

inline auto trim(std::string_view str) -> std::string {
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

inline auto split(std::string_view str, char delim) -> std::vector<std::string> {
    auto splits = str | std::views::split(delim) | std::views::filter([](auto s) { return !s.empty(); });

    auto results = std::vector<std::string>();
    for(auto split: splits) {
        results.emplace_back(split.begin(), split.end());
    }

    return results;
}

constexpr auto contains(std::string_view str, std::string_view search) -> bool {
    return str.find(search) != std::string_view::npos;
}

} // namespace adizzle