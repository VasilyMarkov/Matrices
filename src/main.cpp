#include <iostream>
#include <vector>
#include <optional>
#include <matrices.hpp>
#define TEST

using namespace matrices;

template <typename T>
void print(const std::vector<T>& vec) {
    for(auto const& i : vec) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main() {

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
    std::vector<double> input = {1,2,3,4};
    Matrix m(input, 2);
    std::cout << m;
#endif

    return 0;
}
