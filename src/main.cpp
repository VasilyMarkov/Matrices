#include <iostream>
#include <vector>
#include <optional>
#include <exception>
#include <iterator>
#include <matrices.hpp>
#include <chrono>

using namespace matrices;

template <typename T>
void print(const std::vector<T>& vec) {
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

std::pair<size_t, std::vector<double>> readInputData() {
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
    if(std::cin.fail()) throw std::runtime_error("Invalid input data");
    return {N, data};
}

int main() {
    try {
        auto data = readInputData();
        matr_t<double> matrix(data.first, std::begin(data.second), std::end(data.second));
        auto det =  matrix.det();
        std::cout << det << std::endl;
    }
    catch(std::exception& e)  {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
