#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
namespace matrices {

class Matrix {
private:
    int size_;
    std::unique_ptr<double[]> data_;   
public:
    Matrix() {};
    Matrix(const Matrix& m) {}
    Matrix(const std::vector<double>& vec, size_t size):size_(size), data_(std::make_unique<double[]>(size_*size_))  {
        assert(vec.size() == size_*size_);
        for(auto i = 0; i < vec.size(); ++i) {
            data_[i] = vec[i];
        }
    }

    ~Matrix() = default;
    size_t size() const {return size_;}
    double* operator[](size_t row) { return row * size_ + data_.get(); }
    double& operator()(size_t row, size_t column) const { return data_[row * size_ + column]; }
};

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for(size_t i = 0; i < m.size(); ++i) {
        for(size_t j = 0; j < m.size(); ++j) {
            os << m(i, j) << ' ';
        }
        os << '\n';
    }
    return os;
}        

} 