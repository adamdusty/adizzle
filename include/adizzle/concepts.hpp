#pragma once

#include <concepts>

namespace adizzle {

template<typename T>
concept numeric = std::integral<T> || std::floating_point<T>;

}