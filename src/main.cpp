#include <iostream>
#include <vector>
#include <optional>
#include <exception>
#include <matrices.hpp>
#include <iterator>
#define TEST

using namespace matrices;

template <typename T>
void print(const std::vector<T>& vec) {
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {1,2,3,4,5};
    row_t<int> r(std::begin(data), std::end(data));
    std::cout << r << std::endl;
#ifndef TEST
    size_t N{0};
    std::cin >> N;
    std::vector<double> data(N);
    for(auto i = 0; i < N; ++i) {
        auto tmp{0.0};
        std::cin >> tmp;
        data[i] = tmp;
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