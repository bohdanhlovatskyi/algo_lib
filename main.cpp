// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>

#include "algo_lib.hpp"

template<typename T>
void print_vec(const std::vector<T>& vec) {
    for (const auto& elm : vec) {
        std::cout << elm << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;

    // ---------------------- copy -------------------------
    std::cout << "copy example: " << std::endl;
    std::vector<int> test = {2, 3, 4, 3};
    print_vec(test);

    std::vector<int> res = {};
    res.resize(4);
    ml::copy(test.begin(), test.end(), res.begin());

    std::cout << "copied into: " << std::endl;
    print_vec(res);

    // Won't compile
    // ml::copy(4, 7, res.begin());

    // ---------------------- transform -------------------------
    std::cout << std::endl << "transform example: " << std::endl;
    using namespace std::string_literals;
    auto test2 = {"hello"s, "there"s};
    std::vector<std::string> res2;
    res2.resize(2);

    ml::transform(test2.begin(), test2.end(), res2.begin(),
                  [](const auto& str){ return str + " oopss  ."s; });
    print_vec(res2);

    // ---------------------- reduce -------------------------
    std::cout << std::endl << "reduce example: " << std::endl;
    std::vector<int> test3 = {3, 4, 5};

    auto res3 = ml::map_reduce(test3.begin(), test3.end(),
                           [](auto& num){ return num * num; },
                           [](auto& num1, const auto& num2) { return num1 + num2; });
    std::cout << "reduce result: " << res3 << std::endl;

    return 0;
}
