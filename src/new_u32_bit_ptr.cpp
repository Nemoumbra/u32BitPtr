
#include "new_u32_bit_ptr.hh"

namespace nemo {
    char* u32bit_ptr_common::base = nullptr;

    bool operator==(const typed_u32bit_ptr<void>& first, const typed_u32bit_ptr<void>& second) {
        return first.raw() == second.raw();
    }

    bool operator==(const typed_u32bit_ptr<void>& first, std::nullptr_t) {
        return first.raw() == 0;
    }

    bool operator==(std::nullptr_t, const typed_u32bit_ptr<void>& second) {
        return second.raw() == 0;
    }
}
