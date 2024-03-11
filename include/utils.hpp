#pragma once

double eps = 1e-7;

inline bool equal(const double a, const double b) {
    return std::abs(a-b) < eps;
}
inline bool lessEqual(const double a, const double b) {
    return std::abs(a-b) <= eps;
}
inline bool greaterEqual(const double a, const double b) {
    return std::abs(a-b) >= eps;
}

template<typename T> void construct(T* ptr, T&& rhs) {new (ptr) T(std::forward<T>(rhs));}

template<typename T> void destroy(T* ptr) {ptr->~T();}
template<typename It> void destroy(It begin, It end) {
    while(begin != end) {
        destroy(&*begin++);
    }
}