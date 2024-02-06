#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
namespace matrices {

template<typename T> void construct(T* ptr, T& rhs) { new (ptr) T(rhs);}
template<typename T> void construct(T* ptr, T&& rhs) { new (ptr) T(std::move(rhs));}

template<typename T> void destroy(T* ptr) {ptr->~T();}
template<typename It> void destroy(It begin, It end) {
    while(begin != end) {
        destroy(&*begin++);
    }
}

template<typename T> struct row_buf_t {
protected:
    size_t size_, used_ = 0;
    T* data_ = nullptr;
protected:
    row_buf_t(size_t n = 0):data_(n == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T)*n))), size_(n) {}
    row_buf_t(const row_buf_t& buf) = delete;
    row_buf_t& operator=(const row_buf_t&) = delete; 
    row_buf_t(row_buf_t&& buf) noexcept: size_(buf.size_()), used_(buf.used_), data_(buf.data_) {
        buf.data_ = nullptr;
        buf.size_ = 0;
        buf.used_ = 0;
    };

    row_buf_t& operator=(row_buf_t&& buf) noexcept {
        std::swap(data_, buf.data_()); 
        std::swap(size_, buf.size_());
        std::swap(used_, buf.used_());
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

    explicit row_t(size_t n = 0): row_buf_t<T>(n) {
        while(used_ < size_) {
            construct(data_, 0);
            used_++;
        }
    }

    template<typename It> row_t(It begin, It end): row_buf_t<T>(std::distance(begin, end)) {
        while(begin != end) {
            try {
                construct(data_ + used_++, *begin++);
            }
            catch(std::bad_alloc& e) {
                while(used_ != 0) {
                    destroy(data_+used_--);
                }
                throw std::bad_alloc();
            }
        }
    }

    row_t(const row_t& rhs): row_buf_t<T>(rhs.used_){
        while(used_ < rhs.used_) {
            construct(data_+used_, rhs.data_[used_]);
            used_++;
        }
    }
    row_t& operator=(const row_t& rhs) {
        row_t tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }
    T& operator[](size_t n)
    {
        if(n > used_)
            throw std::out_of_range("Out of range");
        return data_[n];
    }
    const T& operator[](size_t n) const
    {
        if(n > used_)
            throw std::out_of_range("Out of range");
        return data_[n];
    }
    friend std::ostream& operator<<(std::ostream& os, const row_t& r) {
        for(size_t i = 0; i < r.used_; ++i) {
            os << r[i] << ' ';
        }
    return os;
}  
};

template<typename T> struct matr_buf_t {
protected:
    size_t size_, used_ = 0;
    row_t<T>* row_ = nullptr;
protected:
    matr_buf_t(size_t n = 0):row_(n == 0 ? nullptr : static_cast<row_t<T>*>(::operator new(sizeof(row_t<T>)*n))), size_(n) 
    {
        while(used_ < size_) {
            auto curr = row_+used_++;
            // std::cout << curr << std::endl;
            construct(curr, row_t<T>(size_));
        }
    }
    ~matr_buf_t() 
    {
        destroy(row_, row_+used_);
        ::operator delete(row_);
    }
};

template<typename T> struct matr_t: private matr_buf_t<T> {
    using matr_buf_t<T>::used_;
    using matr_buf_t<T>::size_;
    using matr_buf_t<T>::row_;

    explicit matr_t(size_t n = 0): matr_buf_t<T>(n) {}

    template<typename It> matr_t(It begin, It end): matr_buf_t<T>(std::sqrt(std::distance(begin, end))) {
        while(begin != end) {
            construct(row_+used_++, row_t<T>(begin, begin+size_));
            begin+=size_;
        }
    }
    row_t<T>& operator[](size_t n)
    {
        if(n > used_)
            throw std::out_of_range("Out of range");
        return row_[n];
    }
    const row_t<T>& operator[](size_t n) const
    {
        if(n > used_)
            throw std::out_of_range("Out of range");
        return row_[n];
    }
    friend std::ostream& operator<<(std::ostream& os, const matr_t<T>& m) {
        for(size_t i = 0; i < m.used_; ++i) {
            os << m[i] << '\n';
        }
        return os;
    } 
};

} 