#pragma once

#if defined(_WIN32) && defined(__has_include)
#if __has_include(<intrin.h>)
#define DEBUG_BREAK 1
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define BUILTIN_TRAP
#endif