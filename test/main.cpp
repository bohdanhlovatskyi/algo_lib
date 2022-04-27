#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>

TEST(TestMyLib, TestCopyPOD) {
    std::vector<int> v1 = {3, 4, 3, 5};
    std::vector<int> v2(4);

    std::copy(v1.begin(), v1.end(), v2.begin());
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

    std::copy(v1.begin(), v1.end(), v2.begin());
    ASSERT_EQ(v1, v2);

    v2[0] = "sdlfksdfj"s;
    ASSERT_TRUE(v1 != v2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
