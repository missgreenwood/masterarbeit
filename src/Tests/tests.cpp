//  tests.cpp, Judith Greif
//  Description: Unit tests for Masterarbeit (src)

#include <iostream>
#include "gtest/gtest.h"
#include "bloom_filter.hpp"
#include "bloomtest.hpp"

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
