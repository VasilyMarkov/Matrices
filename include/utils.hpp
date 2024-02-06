#pragma once

template<typename T> void construct(T* ptr, T& rhs) { new (ptr) T(rhs);}
template<typename T> void construct(T* ptr, T&& rhs) { new (ptr) T(std::move(rhs));}

template<typename T> void destroy(T* ptr) {ptr->~T();}
template<typename It> void destroy(It begin, It end) {
    while(begin != end) {
        destroy(&*begin++);
    }
}