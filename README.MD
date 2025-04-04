This small library can help with reversing 32bit code by porting it to run on a 64bit machine.

## The general idea
Studying the 32bit apps sometimes brings you to the problem of the devs (accidentally or not) relying on
`sizeof(T*) == 4 == sizeof(uint32_t)`. Or `sizeof(T*) == sizeof(uint32_t) == sizeof(float)`. If you try to rewrite that
on your 64bit machine, you'll break this contract. If the devs don't rely on that, you still end up with a very different memory layout.
I'm aware some compilers might let you build the code with 32bit pointers, but I decided not to try,
because it really doesn't sound very portable. Instead, I've decided to emulate the behavior of 32bit pointers myself.
It's a bit inspired by PPSSPP's class `PSPPointer<T>` (you can see it [here](https://github.com/hrydgard/ppsspp/blob/master/Core/MemMap.h)).
PPSSPP's approach is setting up the hardcoded virtual 32bit memory ranges
and using a bunch of functions for reading from and writing to memory.

This is the second time that I'm dealing with this kind of problem... My old solution was using a
global [remapper](https://github.com/Nemoumbra/PacEngine/tree/master/src/debugger) object
that you have to use every time you wish to interact with the memory pointed to by the 32bit pointer. And before that,
you had to manually register the virtual memory ranges. Every query makes a logarithmic RB-tree search (std::map). This time,
however, I decided to maintain a single virtual memory range by storing a base 64bit pointer as a static class field.
The remapping no longer requires a search, so now it's simply "rebasing" - we construct the host OS pointer by adding the
offset (virtual pointer) to the base.

## The interface
This library provides 2 interfaces: `u32bit_ptr` and `typed_u32bit_ptr<T>`.

The first one is rather experimental, because it's... type-erased! Its API is very different from what you'd expect to see
from a C/C++ pointer: the increment/decrement operators operate in bytes and in order to access the memory, you have to
call `read_as<T>()` for scalar `T` or call `as<T*>()` to get a "handle" `PtrReference` for any `T`.

The second API is typed like normal pointers => it should be very easy to use as a replacement for raw pointers. Well. Almost.

## Limitations
The currently available interfaces suffer from the fact that there can only be one contiguous virtual memory range.
It can be used to model objects with dynamic storage duration, like custom memory managers, allocators, heaps, etc...
But the moment the code tries to reference an object with static or automatic storage duration, we get in trouble, since
no matter how hard we try, the 64bit C++ runtime won't even consider modelling its actions in our virtual RAM => global objects,
string literals, `this` pointer can't be represented by offsets from the base.

Perhaps I'll add the remapper here too later.

## Examples
Check the self-explanatory tests in the `tests` dir.

## Contributing
Sure, why not? PRs and/or issues are welcome.
