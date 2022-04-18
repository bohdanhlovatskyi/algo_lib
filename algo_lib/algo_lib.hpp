#ifndef MY_ALGO_LIB__
#define MY_ALGO_LIB__

namespace ml {
    template<class InputIt, class OutputIt>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt o_first);

    template<class InputIt,
            class OutputIt,
            class UnaryOperation>
    constexpr OutputIt transform( InputIt first1,
                                  InputIt last1,
                                  OutputIt d_first,
                                  UnaryOperation unary_op);

    template<class InputIt1,
            class InputIt2,
            class OutputIt,
            class BinaryOperation >
    constexpr OutputIt transform( InputIt1 first1,
                                  InputIt1 last1,
                                  InputIt2 first2,
                                  OutputIt d_first,
                                  BinaryOperation binary_op);
}

#include "algo_lib.cpp.h"

#endif // MY_ALGO_LIB__