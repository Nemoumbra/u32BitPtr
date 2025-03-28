
#include "u32_bit_ptr.hh"

namespace nemo {
    char* u32bit_ptr::base = nullptr;

    u32bit_ptr operator+(const u32bit_ptr& ptr, ptrdiff_t offset) {
        u32bit_ptr temp{ptr};
        temp += offset;
        return temp;
    }
    ptrdiff_t operator-(const u32bit_ptr& first, const u32bit_ptr& second) {
        return first.raw() - second.raw();
    }
    u32bit_ptr operator-(const u32bit_ptr& ptr, ptrdiff_t offset) {
        u32bit_ptr temp{ptr};
        temp -= offset;
        return temp;
    }

    bool operator==(const u32bit_ptr& first, const u32bit_ptr& second) {
        return first.raw() == second.raw();
    }
}
