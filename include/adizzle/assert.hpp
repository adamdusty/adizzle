#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <string>

#include "adizzle/defs.hpp"

namespace adizzle {

constexpr auto assert(const auto& expr,
                      std::string msg                 = "",
                      const std::source_location& loc = std::source_location::current()) noexcept -> void {
    if(!static_cast<bool>(expr)) {
        std::cerr << std::format(
                         "{}:{}: assertion failed in {}: {}", loc.file_name(), loc.line(), loc.function_name(), msg)
                  << std::endl;
#if DEBUG_BREAK
        ::__debugbreak();
#elif BUILTIN_TRAP
        __builting_trap();
#else
        std::abort();
#endif
    }
}

#if defined(NDEBUG) && NDEBUG
#define ADIZZLE_ASSERT(expr, msg) ((void)(expr))
#else
#define ADIZZLE_ASSERT(expr, msg) adizzle::assert(expr, msg)
#endif

} // namespace adizzle