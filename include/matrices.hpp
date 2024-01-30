#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
namespace matrices {

template<typename T>
struct row_t {
    size_t size;
    T* data = nullptr;
    row_t() {
    };
    row_t(size_t n):size(n), data(new T[size]) 
    {
    }
    ~row_t() { delete [] data;}

    void allocate(size_t n) {
        size = n;
        data = new T[size];
    }
    T& operator[](size_t n)  
    {
        if(n > size)
            throw std::out_of_range("Out of range");
        return data[n];
    }
    const T& operator[](size_t n) const
    {
        if(n > size)
            throw std::out_of_range("Out of range");
        return data[n];
    }
    friend std::ostream& operator<<(std::ostream& os, const row_t& r) {
        for(size_t i = 0; i < r.size; ++i) {
            os << r[i] << ' ';
        }
    return os;
}  
};

template<typename T>
struct matr_t {
    size_t size;
    row_t<T>* rows = nullptr;
    matr_t(size_t n):size(n), rows(new row_t<T>[size]) {
        allocate();
    }
    // static matr_t eye(size_t n) {
    //     size = n;
    //     rows = new row_t<T>[size];
    //     return *this;
    // }
    ~matr_t() {
        delete [] rows;
    }
    row_t<T>& operator[](size_t n)
    {
        if(n > size)
            throw std::out_of_range("Out of range");
        return rows[n];
    }
    const row_t<T>& operator[](size_t n) const
    {
        if(n > size)
            throw std::out_of_range("Out of range");
        return rows[n];
    }
    void allocate() {
        for(auto i = 0; i < size; ++i) {
            rows[i].allocate(size);
        }
        fill(0);
    }
    void fill(T value) {
        for(auto i = 0; i < size; ++i) {
            for(auto j = 0; j < size; ++j) {
                rows[i][j] = value;
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const matr_t<T>& m) {
        for(size_t i = 0; i < m.size; ++i) {
            os << m[i] << '\n';
        }
        return os;
    } 
};

} 