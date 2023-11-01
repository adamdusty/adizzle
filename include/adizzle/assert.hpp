#pragma once

#include <format>
#include <iostream>
#include <source_location>

#if defined(_WIN32) && defined(__has_include)
#if __has_include(<intrin.h>)
#define DEBUG_BREAK 1
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define BUILTIN_TRAP 1
#endif

namespace adizzle {

constexpr auto assert(const auto& expr,
                      const char* msg                                 = "",
                      [[maybe_unused]] const std::source_location loc = std::source_location::current()) noexcept
    -> void {
    if(!expr) {
        std::cerr << std::format(
                         "{}:{}: assertion failed in {}: {}", loc.file_name(), loc.line(), loc.function_name(), msg)
                  << std::endl;
#if DEBUG_BREAK
        ::__debugbreak();
#elif BUILTIN_TRAP
        __builtin_trap();
#else
        std::abort();
#endif
    }
}

} // namespace adizzle