#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "../algo_lib/algo_lib.hpp"

TEST(TestMyLib, TestCopyPOD) {
    std::vector<int> v1 = {3, 4, 3, 5};
    std::vector<int> v2(4);

    ml::copy(v1.begin(), v1.end(), v2.begin());
    ASSERT_EQ(v1, v2);

    v2[0] = 9;
    ASSERT_TRUE(v1 != v2);
}

TEST(TestMyLib, TestCopyNotPOD) {
    using namespace std::string_literals;
    std::vector<std::string> v1 = {"3"s, "4"s, "3"s,
       "vvery vveeeeeeeeeeeeeeeeeeeeeery vveeeeeeeeeeeeeeeeeeeeeery vveeeeeeeeeeeeeeeeeeeeeery"
       "vveeeeeeeeeeeeeeeeeeeeeer yveeeeeeeeeeeeeeeeeeeeeer yvveeeeeeeeeeeeeeeeeeeeeery long string"s
    };
    std::vector<std::string> v2(4);

    ml::copy(v1.begin(), v1.end(), v2.begin());
    ASSERT_EQ(v1, v2);

    v2[0] = "sdlfksdfj"s;
    ASSERT_TRUE(v1 != v2);
}

TEST(TestMyLib, TestTransform) {
    std::vector<int> v1 = {3, 4, 3, 5};
    std::vector<int> v3 = {6, 8, 6, 10};
    std::vector<int> v2(4);

    ml::transform(v1.begin(), v1.end(), v2.begin(),
                  [](const auto& x){ return x * 2; });
    ASSERT_EQ(v3, v2);
}

TEST(TestMyLib, TestTransformEmpty) {
    std::vector<int> v1 = {};
    std::vector<int> v3 = {};
    std::vector<int> v2;

    ml::transform(v1.begin(), v1.end(), v2.begin(),
                  [](const auto& x){ return x * 2; });
    ASSERT_EQ(v3, v2);
}

TEST(TestMyLib, TestTwoTransform) {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {4, 3, 2, 1};
    std::vector<int> v3 = {5, 5, 5, 5};
    std::vector<int> v4(4);

    ml::transform(v1.begin(), v1.end(), v2.begin(), v4.begin(),
                  [](const auto& x, const auto& y){ return x + y; });
    ASSERT_EQ(v3, v4);
}

TEST(TestMyLib, TestTwoTransformForComplexType) {
    using namespace std::string_literals;
    std::vector<std::string> v1 = {"1"s, "2"s, "3"s, "4"s};
    std::vector<std::string> v2 = {"4"s, "3"s, "2"s, "1"s};
    std::vector<std::string> v3 = {"14"s, "23"s, "32"s, "41"s};
    std::vector<std::string> v4(4);

    ml::transform(v1.begin(), v1.end(), v2.begin(), v4.begin(),
                  [](const auto& x, const auto& y){ return x + y; });
    ASSERT_EQ(v3, v4);
}

TEST(TestMyLib, TestSumOfSquares) {
    std::vector<int> test = {3, 4, 5};
    int expected = 50;

    auto res = ml::map_reduce(test.begin(), test.end(),
                  [](const auto& x) { return x * x; },
                  [](const auto& x, const auto& y){ return x + y; });
    ASSERT_EQ(expected, res);
}

TEST(TestMyLib, TestLongestString) {
    using namespace std::string_literals;
    std::vector<std::string> test = {"hello"s, "there"s, "how"s, "are"s, "you", "doing?"};
    std::string expected = "doing?"s;

    auto res = ml::map_reduce(test.begin(), test.end(),
                              [](const auto& x) { return x; },
                              [](const auto& x, const auto& y){
        return x.size() > y.size() ? x : y;
    });

    ASSERT_EQ(expected, res);
}

TEST(TestMyLib, TestCountWords) {
    using fsp = std::filesystem::path;
    std::vector<fsp> paths = {"../data/test1.txt", "../data/test2.txt"};
    std::map<std::string, size_t> expected = {
            {"hello", 3},
            {"there", 1}
    };

    auto res = ml::map_reduce(paths.begin(), paths.end(),
        // transform paths into maps via mapper
        [](const auto& x) {
            std::string word;
            std::map<std::string, size_t> res;

            // read file into memory
            std::ifstream raw_file(x);
            std::stringstream ss{};
            ss << raw_file.rdbuf();

            // count words for this fie
            while (ss >> word) {
                res[word] += 1;
            }

            return res;
        },
        // merge the dicts via reducer
        [](auto& x, const auto& y){
            for (const auto& [k, v] : y) {
                x[k] += v;
            }

            return x;
        });

    ASSERT_EQ(expected, res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
