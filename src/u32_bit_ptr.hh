#pragma once

#include <cstring>
#include <type_traits>

#include "../utils.hh"

namespace nemo {
    class u32bit_ptr {
    private:
        u32 ram_offset;
        static char* base;
    public:
        static void rebase(char* new_base) {
            base = new_base;
        }

        u32bit_ptr() = default;
        u32bit_ptr(const u32bit_ptr& other) = default;
        u32bit_ptr(u32bit_ptr&& other) = default;
        u32bit_ptr& operator=(const u32bit_ptr& other) = default;
        u32bit_ptr& operator=(u32bit_ptr&& other) = default;
        ~u32bit_ptr() = default;

        explicit u32bit_ptr(u32 value): ram_offset(value) {}

        // implicit
        u32bit_ptr(std::nullptr_t): ram_offset(0) {}

        // Host ptr assignment
        u32bit_ptr& operator=(const void* ptr) {
            // rebase ptr
            ram_offset = static_cast<const char*>(ptr) - base;
            return *this;
        }

        // NB! delta is in bytes
        u32bit_ptr& operator+=(ptrdiff_t delta) {
            ram_offset += delta;
            return *this;
        }
        // NB! delta is in bytes
        u32bit_ptr& operator-=(ptrdiff_t delta) {
            ram_offset -= delta;
            return *this;
        }
        // Deliberately not overloading ++ and --

        u32 raw() const {
            return ram_offset;
        }

        char* host_ptr() const {
            return base + ram_offset;
        }

        template <Scalar T>
        T read_as() {
            T storage;
            std::memcpy(&storage, host_ptr(), sizeof(storage));
            return storage;
        }

        // If you want to do a static_cast to host ptr
        template <Pointer Ptr>
        explicit operator Ptr() {
            return reinterpret_cast<Ptr>(host_ptr());
        }

        template <Pointer Ptr>
        struct PtrReference {
            using Underlying = std::remove_pointer_t<Ptr>;
            Ptr ptr;

            PtrReference& operator=(Underlying value) {
                *ptr = value;
                return *this;
            }
            const Underlying& operator[](ptrdiff_t index) const {
                return ptr[index];
            }

            Underlying& operator[](ptrdiff_t index) {
                return ptr[index];
            }

            explicit PtrReference(Ptr ptr) : ptr(ptr) {}
        };

        template <Pointer Ptr>
        auto as() {
            return PtrReference<Ptr>(reinterpret_cast<Ptr>(host_ptr()));
        }
    };

    u32bit_ptr operator+(const u32bit_ptr& ptr, ptrdiff_t offset);
    u32bit_ptr operator-(const u32bit_ptr& ptr, ptrdiff_t offset);
}
