#ifndef MY_ALGO_LIB_REALISATION__
#define MY_ALGO_LIB_REALISATION__

// TODO: remove this from here
#define DEBUG true

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace ml {
    template<class InputIt, class OutputIt>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt o_first) {
        std::cout << "hello there copy" << std::endl;
    }
}

#endif // MY_ALGO_LIB_REALISATION__