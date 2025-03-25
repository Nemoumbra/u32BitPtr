#pragma once

#include "../new_u32_bit_ptr.hh"

namespace new_tests {
    using namespace nemo;

    template <typename T>
    T* build_default(char* ptr) {
        return new (ptr) T();
    }

    struct Object {
        u32 mask{0x0};
        u32 value{0xdeadbeef};
        typed_u32bit_ptr<u32> stack_top{}; // replacement for 'u32* stack_top;'
        u32 flags{0x0};
        u32 stack[8]{}; // at offset 16
        float time{0.5f};
        // in total 48 + sizeof(float) bytes

        ~Object() = default; // trivially destructible, by the way
    };

    void new_test();
}