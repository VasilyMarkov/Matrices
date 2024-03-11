#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
#include <utils.hpp>
#include <row.hpp>
#include <optional>
#include <type_traits>

namespace matrices {

template<typename T, typename = typename std::enable_if<std::is_convertible<T, double>::value>>
struct matr_buf_t {
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
        while(begin != end) {
            construct(row_+used_++, row_t<T>(begin, begin+size_));
            begin+=size_;
        }
    }

    matr_t(const matr_t& rhs): matr_t<T>(rhs.used_){
        while(used_ < rhs.used_) {
            construct(row_+used_, row_t<T>(rhs[used_]));
            used_++;
        }
    }

    matr_t(matr_t&& rhs): matr_buf_t<T>(std::move(rhs)) {}

    row_t<T>& operator[](size_t n) { return row_[n]; }

    const row_t<T>& operator[](size_t n) const { return row_[n]; }

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
    
    friend std::ostream& operator<<(std::ostream& os, const matr_t<T>& m) {
        for(size_t i = 0; i < m.used_; ++i) {
            os << m[i] << '\n';
        }
        return os;
    } 

    double det() { 
        auto result = gaussJordan();
        if(result == std::nullopt) return 0;  

        global_permutation = result.value();

        return global_permutation*diagonalProduct();
    }

private:

    int global_permutation = 1;

    double diagonalProduct() const noexcept {
        double result = 1;
        for(auto i = 0; i < size_; ++i) {
            result *= row_[i][i];
        }
        return result;
    }

    std::optional<int> gaussJordan() noexcept {
        double temp = 0;
        size_t permutations = 0;
        for(auto j = 0; j < size_; ++j) {
            double max = 0;
            size_t max_ind = 0;
            for(auto i = j; i < size_; ++i) {
                if(auto row_max = std::fabs(row_[i][j]); row_max > max) {
                    max = row_max;
                    max_ind = i;
                }
            }

            swap(row_[j], row_[max_ind]);
            
            if (j != max_ind) permutations++;
            if (std::fabs(row_[j][j]) < eps) 
                return std::nullopt;

            for(auto i = 0; i < size_; ++i) {
                if(i != j)
                {
                    temp = row_[i][j]/row_[j][j];

                    for(auto k = 0; k < size_; ++k) {
                        row_[i][k] -= row_[j][k]*temp;
                    }
                }
            }
            
        }
        int local_permutation = -1;

        if(permutations % 2 == 0) local_permutation = 1;

        return local_permutation*global_permutation;
    }
};

} 
