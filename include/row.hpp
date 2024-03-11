#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
#include "utils.hpp"
namespace matrices {

template<typename T, typename = typename std::enable_if<std::is_convertible<T, double>::value>> 
struct row_buf_t {
protected:
    size_t size_, used_ = 0;
    T* data_ = nullptr;
protected:
    row_buf_t(const row_buf_t& buf) = delete;
    row_buf_t& operator=(const row_buf_t&) = delete; 

    row_buf_t(size_t n = 0):data_(n == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T)*n))), size_(n) {}

    row_buf_t(row_buf_t&& buf) noexcept: size_(buf.size_), used_(buf.used_), data_(buf.data_) {
        buf.size_ = 0;
        buf.used_ = 0;
        buf.data_ = nullptr;
    };

    row_buf_t& operator=(row_buf_t&& buf) noexcept {
        std::swap(data_, buf.data_); 
        std::swap(size_, buf.size_);
        std::swap(used_, buf.used_);
        return *this;
    };

    ~row_buf_t() {
        destroy(data_, data_ + used_);
        ::operator delete(data_);
    };
};

template<typename T> struct row_t: private row_buf_t<T> {
    using row_buf_t<T>::used_;
    using row_buf_t<T>::size_;
    using row_buf_t<T>::data_;

    explicit row_t(size_t n = 0): row_buf_t<T>(n) {}

    static row_t eye(size_t n = 0) {
        row_t<T> row(n);
        while(row.used_ < row.size_) {
            construct(row.data_ + row.used_++, static_cast<T>(1));
        }
        return row;
    }

    template<typename It> row_t(It begin, It end): row_buf_t<T>(std::distance(begin, end)) {
        while(begin != end) {
            auto it = *begin++;
            construct(data_ + used_++, std::move(it));
        }
    }

    row_t(const row_t& rhs): row_buf_t<T>(rhs.used_){
        while(used_ < rhs.used_) {
            construct(data_+used_, std::move(rhs.data_[used_]));
            used_++;
        }
    }

    row_t(row_t&& rhs): row_buf_t<T>(std::move(rhs)){}
    
    row_t& operator=(row_t&& rhs) = default;

    row_t& operator=(const row_t& rhs) {
        row_t tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }

    T& operator[](size_t n) { return data_[n]; }

    const T& operator[](size_t n) const { return data_[n]; }

    bool operator==(const row_t& rhs) const noexcept {
        auto result = true;
        for(auto i = 0; i < size_; ++i) {
            if(!equal(data_[i], rhs[i])) {
                result = false;
                break;
            }
        }
        return result;
    }

    row_t& operator-=(const row_t& rhs) noexcept {
        for(auto i = 0; i < size_; ++i) {
            data_[i] -= rhs[i];
        }  
        return *this;
    }

    friend row_t operator-(const row_t& rhs, const row_t& lhs) noexcept {
        auto tmp = rhs;
        for(auto i = 0; i < size_; ++i) {
                tmp[i] -= lhs[i];
        }  
        return tmp;
    }

    friend void swap(row_t& rhs, row_t& lhs) noexcept {
        auto tmp = std::move(rhs);
        rhs = std::move(lhs);
        lhs = std::move(tmp);
    }

    friend std::ostream& operator<<(std::ostream& os, const row_t& r) {
        for(size_t i = 0; i < r.used_; ++i) {
            os << r[i] << ' ';
        }
        return os;
    }  
};

}