#ifndef MY_ALGO_LIB__
#define MY_ALGO_LIB__

// needs to be included before <string>
#if defined(__STDC_LIB_EXT1__)
#define __STDC_WANT_LIB_EXT1__ 1
#endif

namespace {
    // takes into account difference between POD and not POD types
    template<class InputIt,
            class OutputIt,
            std::enable_if_t<!std::is_trivially_copyable_v<
                    typename std::iterator_traits<InputIt>::value_type>, bool> = true>
    constexpr OutputIt copy_(InputIt first, InputIt last, OutputIt o_first, std::input_iterator_tag) {
        // call copy assignment for each of the elements
        for (; first != last; ++first, ++o_first) {
            *o_first = *first;
        }

        return o_first;
    }

    /*
     * If supported by standard lib, destination range will be zeroed:
     *      - the source and the destination objects overlap
     *      - count is greater than destination buffer size (buffer overflow would occur)
     *      - dest or src is a null pointer
     */
    template<class InputIt,
            class OutputIt,
            std::enable_if_t<std::is_trivially_copyable_v<
                    typename std::iterator_traits<InputIt>::value_type>, bool> = true>
    constexpr OutputIt copy_(InputIt first, InputIt last, OutputIt o_first, std::input_iterator_tag) {
        using underlying_type = typename std::iterator_traits<InputIt>::value_type;
#if defined(__STDC_LIB_EXT1__)
        memcpy_s(&*o_first, &*first, (last - first) * sizeof(underlying_type));
#endif
        memcpy(&*o_first, &*first, (last - first) * sizeof(underlying_type));
        return o_first;
    }
}

namespace ml {
    // takes into account difference between POD and not POD types
    template<class InputIt,
            class OutputIt,
            std::enable_if_t<!std::is_trivially_copyable_v<
                            typename std::iterator_traits<InputIt>::value_type>, bool> = true>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt o_first) {
        copy_(first, last, o_first, typename std::iterator_traits<OutputIt>::iterator_category());
        return o_first;
    }

    /*
     * If supported by standard lib, destination range will be zeroed:
     *      - the source and the destination objects overlap
     *      - count is greater than destination buffer size (buffer overflow would occur)
     *      - dest or src is a null pointer
     */
    template<class InputIt,
            class OutputIt,
            std::enable_if_t<std::is_trivially_copyable_v<
                    typename std::iterator_traits<InputIt>::value_type>, bool> = true>
    constexpr OutputIt copy(InputIt first, InputIt last, OutputIt o_first) {
        copy_(first, last, o_first, typename std::iterator_traits<OutputIt>::iterator_category());
        return o_first;
    }

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

#endif // MY_ALGO_LIB__