#include <iostream>
#include <vector>
#include <optional>
#include <exception>
#include <iterator>
#include <matrices.hpp>
#include <chrono>
// #define TEST

using namespace matrices;

template <typename T>
void print(const std::vector<T>& vec) {
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

int main() {

#ifndef TEST
    double tmp{0};
    size_t N{0};
    std::cin >> tmp;
    N = static_cast<size_t>(tmp);
    std::vector<double> data(N*N);
    for(auto i = 0; i < N*N; ++i) {
        auto tmp{0.0};
        std::cin >> tmp;
        data[i] = tmp;
    }  
    try {
        matr_t<double> matrix(N, std::begin(data), std::end(data));
        std::cout << matrix;
        auto begin = std::chrono::high_resolution_clock::now();
        auto det =  matrix.det();
        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << det << std::endl;
        std::cout << delta << " ms";
    }
    catch(std::exception& e)  {
        std::cout << e.what() << std::endl;
    }
#else
    // std::vector<int> input = {1,2,3,4};
    // row_t<int> r(std::begin(input), std::end(input));
    // try
    // {
    //     std::cout << r << std::endl;
    // } 
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
#endif

    return 0;
}
