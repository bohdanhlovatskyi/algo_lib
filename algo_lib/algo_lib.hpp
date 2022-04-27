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
    constexpr OutputIt copy_(InputIt first, InputIt last,
                             OutputIt o_first, std::input_iterator_tag) {
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
    constexpr OutputIt copy_(InputIt first, InputIt last,
                             OutputIt o_first, std::input_iterator_tag) {
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
        copy_(first, last, o_first,
              typename std::iterator_traits<OutputIt>::iterator_category());
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
        copy_(first, last, o_first,
              typename std::iterator_traits<OutputIt>::iterator_category());
        return o_first;
    }

    template<class InputIt, class OutputIt, class UnaryOperation>
    constexpr OutputIt transform( InputIt first, InputIt last,
                                  OutputIt d_first, UnaryOperation unary_op) {

        while (first != last) {
            *d_first = unary_op(*first);
            ++first; ++d_first;
        }

        return d_first;
    }

    template<class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
    constexpr OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2,
                                  OutputIt d_first, BinaryOp bin_op) {

        while (first1 != last1) {
            *d_first = bin_op(*first1, *first2);
            ++first1; ++first2; ++d_first;
        }

        return d_first;
    }

    template<class InputIt, class BinaryOperation>
    constexpr decltype(auto) reduce( InputIt first, InputIt last,
                           BinaryOperation reducer) {
        using T = typename std::iterator_traits<InputIt>::value_type;

        T result = *first++;
        while (first != last) {
            result = reducer(result, *first);
            first++;
        }

        return result;
    }

    template<class InputIt, class UnaryOperatrion, class BinaryOperation>
    constexpr decltype(auto) map_reduce( InputIt first, InputIt last,
                                         UnaryOperatrion mapper,
                                         BinaryOperation reducer)
    {
        using UT = typename std::iterator_traits<InputIt>::value_type;
        using diff = typename std::iterator_traits<InputIt>::difference_type;

        const diff size = last - first;
        UT* tmp = (UT* ) ::operator new(size * sizeof(UT));

        ml::transform(first, last, tmp, mapper);
        auto res = reduce(tmp, tmp + size, reducer);

        operator delete(tmp);

        return res;
    }
}

#endif // MY_ALGO_LIB__