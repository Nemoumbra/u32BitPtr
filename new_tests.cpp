#include <memory>
#include <cassert>


#include "new_tests.hh"

namespace new_tests {
    void new_test() {
        constexpr u32 chunk_size = 1024 * 1024;
        auto memory_raii = std::make_unique<char[]>(chunk_size);
        auto* raw_ptr = memory_raii.get();
        u32bit_ptr_common::rebase(raw_ptr);


        static_assert(sizeof(Object) == 48 + sizeof(float));
        auto* ptr = build_default<Object>(raw_ptr);
        auto& object = *ptr;
        auto& stack_top_ptr = object.stack_top;

        stack_top_ptr = object.stack;
        assert(stack_top_ptr.raw() == 16);

        object.stack[2] = 0x5;
        assert(stack_top_ptr[2] == 0x5);

        auto float_ptr = typed_u32bit_ptr<float>(stack_top_ptr + std::ssize(object.stack));
        assert(float_ptr.read() == object.time);
        assert(*float_ptr == object.time);

        stack_top_ptr -= 3;
        assert(stack_top_ptr.read() == object.value);

        assert(stack_top_ptr - 1 == nullptr);

        typed_u32bit_ptr<Object> self(0x0u);
        self->mask |= 0x1;
        assert(object.mask == 0x1);

        auto& value = self->value;
        *stack_top_ptr = 0x7;
        assert(value == 0x7);

        typed_u32bit_ptr<void> void_ptr(self);

        assert(void_ptr == stack_top_ptr - 1);

    }
}