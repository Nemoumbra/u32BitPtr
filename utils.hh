#pragma once

#include <cstdint>
#include <type_traits>


namespace nemo {
    using u32 = std::uint32_t;

    template <typename T>
    concept Pointer = std::is_pointer_v<T>;

    template <typename T>
    concept Scalar = std::is_scalar_v<T>;
}