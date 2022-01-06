#include "stdio.h"
#include "tests_main.h"
#include "../ring_buffer/ring_buff.h"
#include <gtest/gtest.h>
#include "tests_body.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}