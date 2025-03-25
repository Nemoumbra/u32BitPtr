#pragma once

#include <cstring>
#include <type_traits>

#include "utils.hh"


namespace nemo {
    class u32bit_ptr_common {
    protected:
        static char* base; // not inherited

        u32 ram_offset;

        u32bit_ptr_common() = default;
        u32bit_ptr_common(const u32bit_ptr_common& other) = default;
        u32bit_ptr_common(u32bit_ptr_common&& other) = default;
        u32bit_ptr_common& operator=(const u32bit_ptr_common& other) = default;
        u32bit_ptr_common& operator=(u32bit_ptr_common&& other) = default;
        ~u32bit_ptr_common() = default;

        explicit u32bit_ptr_common(u32 value): ram_offset(value) {}

    public:
        // not inherited
        static void rebase(char* new_base) {
            base = new_base;
        }

        u32 raw() const {
            return ram_offset;
        }

        char* host_ptr() const {
            return base + ram_offset;
        }
    };

    template <typename T>
    class typed_u32bit_ptr: public u32bit_ptr_common {
    public:
        using ConstT = const T;
        using Ptr = T*;
        using ConstPtr = ConstT*;
        using Ref = T&;
        using ConstRef = ConstT&;

        typed_u32bit_ptr() = default;
        typed_u32bit_ptr(const typed_u32bit_ptr& other) = default;
        typed_u32bit_ptr(typed_u32bit_ptr&& other) = default;
        typed_u32bit_ptr& operator=(const typed_u32bit_ptr& other) = default;
        typed_u32bit_ptr& operator=(typed_u32bit_ptr&& other) = default;
        ~typed_u32bit_ptr() = default;

        explicit typed_u32bit_ptr(u32 value): u32bit_ptr_common(value) {}

        // implicit
        typed_u32bit_ptr(std::nullptr_t): u32bit_ptr_common(0) {}

        // Explicit coercion ctor
        template <typename U>
        explicit typed_u32bit_ptr(const typed_u32bit_ptr<U>& other): u32bit_ptr_common(other.raw()) {}

        // Host ptr assignment
        typed_u32bit_ptr& operator=(ConstPtr ptr) {
            // rebase ptr
            ram_offset = reinterpret_cast<const char*>(ptr) - base;
            return *this;
        }

        typed_u32bit_ptr& operator+=(ptrdiff_t delta) {
            ram_offset += delta * sizeof(T);
            return *this;
        }
        typed_u32bit_ptr& operator-=(ptrdiff_t delta) {
            ram_offset -= delta * sizeof(T);
            return *this;
        }

        typed_u32bit_ptr& operator++() {
            ram_offset += sizeof(T);
            return *this;
        }
        typed_u32bit_ptr& operator--() {
            ram_offset -= sizeof(T);
            return *this;
        }

        typed_u32bit_ptr operator++(int) {
            typed_u32bit_ptr copy(*this);

            ram_offset += sizeof(T);
            return copy;
        }
        typed_u32bit_ptr operator--(int) {
            typed_u32bit_ptr copy(*this);

            ram_offset -= sizeof(T);
            return copy;
        }

        Ref operator*() {
            return *reinterpret_cast<Ptr>(host_ptr());
        }
        ConstRef operator*() const {
            return *reinterpret_cast<Ptr>(host_ptr());
        }

        Ptr operator->() {
            return reinterpret_cast<Ptr>(host_ptr());
        }
        ConstPtr operator->() const {
            return reinterpret_cast<Ptr>(host_ptr());
        }

        Ref operator[](ptrdiff_t index) {
            auto* rebased = operator->();
            return rebased[index];
        }
        ConstRef operator[](ptrdiff_t index) const {
            auto* rebased = operator->();
            return rebased[index];
        }

        T read() requires Scalar<T> {
            T storage;
            std::memcpy(&storage, host_ptr(), sizeof(storage));
            return storage;
        }
    };

    template <typename T>
    typed_u32bit_ptr<T> operator+(const typed_u32bit_ptr<T>& ptr, ptrdiff_t offset) {
        typed_u32bit_ptr<T> temp{ptr};
        temp += offset;
        return temp;
    }
    template <typename T>
    typed_u32bit_ptr<T> operator+(ptrdiff_t offset, const typed_u32bit_ptr<T>& ptr) {
        typed_u32bit_ptr<T> temp{ptr};
        temp += offset;
        return temp;
    }

    template <typename T>
    ptrdiff_t operator-(const typed_u32bit_ptr<T>& first, const typed_u32bit_ptr<T>& second) {
        return first.raw() - second.raw();
    }

    template <typename T>
    typed_u32bit_ptr<T> operator-(const typed_u32bit_ptr<T>& ptr, ptrdiff_t offset) {
        typed_u32bit_ptr<T> temp{ptr};
        temp -= offset;
        return temp;
    }

    template <typename T>
    bool operator==(const typed_u32bit_ptr<T>& first, const typed_u32bit_ptr<T>& second) {
        return first.raw() == second.raw();
    }
    template <typename T>
    bool operator==(const typed_u32bit_ptr<T>& first, std::nullptr_t) {
        return first.raw() == 0;
    }
    template <typename T>
    bool operator==(std::nullptr_t, const typed_u32bit_ptr<T>& second) {
        return second.raw() == 0;
    }


    template <>
    class typed_u32bit_ptr<void>: public u32bit_ptr_common {
    public:
        using ConstT = const void;
        using Ptr = void*;
        using ConstPtr = ConstT*;

        typed_u32bit_ptr() = default;
        typed_u32bit_ptr(const typed_u32bit_ptr& other) = default;
        typed_u32bit_ptr(typed_u32bit_ptr&& other) = default;
        typed_u32bit_ptr& operator=(const typed_u32bit_ptr& other) = default;
        typed_u32bit_ptr& operator=(typed_u32bit_ptr&& other) = default;
        ~typed_u32bit_ptr() = default;

        explicit typed_u32bit_ptr(u32 value): u32bit_ptr_common(value) {}

        // implicit
        typed_u32bit_ptr(std::nullptr_t): u32bit_ptr_common(0) {}

        // Implicit coercion ctor
        template <typename U>
        typed_u32bit_ptr(const typed_u32bit_ptr<U>& other): u32bit_ptr_common(other.raw()) {}

        // Host ptr assignment
        typed_u32bit_ptr& operator=(ConstPtr ptr) {
            // rebase ptr
            ram_offset = static_cast<const char*>(ptr) - base;
            return *this;
        }
        Ptr operator->() {
            return reinterpret_cast<Ptr>(host_ptr());
        }
        ConstPtr operator->() const {
            return reinterpret_cast<Ptr>(host_ptr());
        }
    };

    bool operator==(const typed_u32bit_ptr<void>& first, const typed_u32bit_ptr<void>& second);

    bool operator==(const typed_u32bit_ptr<void>& first, std::nullptr_t);

    bool operator==(std::nullptr_t, const typed_u32bit_ptr<void>& second);
}

