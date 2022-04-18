// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>

#include "algo_lib.hpp"

int main(int argc, char* argv[]) {
    std::vector<int> test = {2, 3, 4, 3};
    std::vector<int> res{};

    ml::copy(test.begin(), test.end(), res.begin());

    return 0;
}
