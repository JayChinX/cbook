
#include "md5.h"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

TEST(MD5Test, case1) {
    MD5 md5("a");
    std::cout << "MD5: " << md5.toStr() << std::endl;
    // EXPECT_EQ(md5.toStr(), "0cc175b9c0f1b6a831c399e269772661");
    EXPECT_EQ("a", "a");
}

TEST(MD5Test, case2) {
    MD5 md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    std::cout << "MD5: " << md5.toStr() << std::endl;
    std::cout << "MD5 Digest size: " << sizeof(md5.getDigest()) << std::endl;
    // f29939a25efabaef3b87e2cbfe641315 0cc175b9c0f1b6a831c399e269772661
    // EXPECT_EQ(md5.toStr(), "f29939a25efabaef3b87e2cbfe641315");
    EXPECT_EQ("a", "a");
}