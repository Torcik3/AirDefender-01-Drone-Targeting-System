#pragma once
#include <iostream>

template<typename T>
struct Allocator {

    static T* Allocate(unsigned long long count) {
        return static_cast<T*>(::operator new[](count*sizeof(T)));
    }

    static void Deallocate(T* block,unsigned long long count) {
        ::operator delete(block);
    }

template<typename... Args>
    static void Constructor(T* target, Args&&... args) {

        new(target) T(std::forward<Args>(args)...);
    }
static void Destroy(T* target) {
        target->~T();
    }

};