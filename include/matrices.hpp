#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
#include <utils.hpp>
#include <row.hpp>

namespace matrices {

template<typename T> struct matr_buf_t {
protected:
    size_t size_, used_ = 0;
    row_t<T>* row_ = nullptr;
protected:
    matr_buf_t(const matr_buf_t&) = delete;
    matr_buf_t& operator=(const matr_buf_t&) = delete;

    matr_buf_t(size_t n = 0):row_(n == 0 ? nullptr : static_cast<row_t<T>*>(::operator new(sizeof(row_t<T>)*n))), size_(n) {}
    matr_buf_t(matr_buf_t&& rhs) noexcept : size_(rhs.size_), used_(rhs.used_), row_(rhs.row_) {
        rhs.size_ = 0;
        rhs.used_ = 0;
        rhs.row_ = nullptr;
    }
    matr_buf_t& operator=(matr_buf_t&& rhs) noexcept {
        std::swap(size_, rhs.size_);
        std::swap(used_, rhs.used_);
        std::swap(row_, rhs.row_);
    }   
    ~matr_buf_t() {
        destroy(row_, row_+used_);
        ::operator delete(row_);
    }
};

template<typename T> struct matr_t: private matr_buf_t<T> {
    using matr_buf_t<T>::used_;
    using matr_buf_t<T>::size_;
    using matr_buf_t<T>::row_;

    explicit matr_t(size_t n = 0): matr_buf_t<T>(n) {}

    template<typename It> matr_t(size_t size, It begin, It end): matr_buf_t<T>(size) {
        if(std::distance(begin, end) != size_ * size_) throw std::runtime_error("non square matrix");
        
        try {
            while(begin != end) {
                construct(row_+used_++, row_t<T>(begin, begin+size_));
                begin+=size_;
            }
        }
        catch(std::bad_alloc& e) {
            destroy(row_, row_+used_);
            used_ = 0;
            throw std::bad_alloc();
        }

    }

    row_t<T>& operator[](size_t n) {
        if(n > used_)
            throw std::out_of_range("out of range");
        return row_[n];
    }

    const row_t<T>& operator[](size_t n) const {
        if(n > used_)
            throw std::out_of_range("out of range");
        return row_[n];
    }

    bool operator==(const matr_t& rhs) const noexcept {
        auto result = true;
        for(auto i = 0; i < size_; ++i) {
            for(auto j = 0; j < size_; ++j) {
                if(!equal(row_[i][j], rhs[i][j])) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    matr_t& operator-=(double sub) {
        for(auto i = 0; i < size_; ++i) {
            for(auto j = 0; j < size_; ++j) {
                row_[i][j] -= sub;
            }
        }  
        return *this;
    }

    matr_t& operator/=(double divisor) {
        for(auto i = 0; i < size_; ++i) {
            for(auto j = 0; j < size_; ++j) {
                row_[i][j] /= divisor;
            }
        }  
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const matr_t<T>& m) {
        for(size_t i = 0; i < m.used_; ++i) {
            os << m[i] << '\n';
        }
        return os;
    } 

    double det() {
        try {
            gaussJordan();   
        }
        catch(std::runtime_error& e) {
            return 0;
        }
        return diagonalProduct();
    }

private:
    double diagonalProduct() const noexcept {
        double result = 1;
        for(auto i = 0; i < size_; ++i) {
            result *= row_[i][i];
        }
        return result;
    }

    void gaussJordan() {
        double temp = 0;
        for(auto j = 0; j < size_; ++j) {
            for(auto i = 0; i < size_; ++i) {
                if(i != j)
                {
                    if(std::fabs(row_[j][j]) < eps) throw std::runtime_error("degenerate matrix");
                    temp = row_[i][j]/row_[j][j];

                    for(auto k = 0; k < size_; ++k) {
                        row_[i][k] -= row_[j][k]*temp;
                    }
                }
            }
        }
    }
};

} 