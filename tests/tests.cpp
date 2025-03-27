#include <memory>
#include <cassert>


#include "tests.hh"

namespace tests {
    void test() {
        constexpr u32 chunk_size = 1024 * 1024;
        auto memory_raii = std::make_unique<char[]>(chunk_size);
        auto* raw_ptr = memory_raii.get();
        u32bit_ptr::rebase(raw_ptr);


        static_assert(sizeof(Object) == 48 + sizeof(float));
        auto* ptr = build_default<Object>(raw_ptr);
        auto& object = *ptr;
        auto& stack_top_ptr = object.stack_top;

        stack_top_ptr = &object.stack;
        assert(stack_top_ptr.raw() == 16);

        object.stack[2] = 0x5;
        assert(stack_top_ptr.as<u32*>()[2] == 0x5);

        auto float_ptr = stack_top_ptr + sizeof(object.stack);
        assert(float_ptr.read_as<float>() == object.time);

        stack_top_ptr -= sizeof(object.flags) + sizeof(object.stack_top) + sizeof(object.value);
        assert(stack_top_ptr.read_as<u32>() == object.value);

        // assert(stack_top_ptr - sizeof(object.mask) == nullptr);
        // WTF
    }
}

int main() {
    tests::test();
}