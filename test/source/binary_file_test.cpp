//
// Created by kuper on 11.02.2024.
//
#include "b3dm-cpp/binary_file.h"

#include <gtest/gtest.h>

TEST(BinaryFileTest, OkState) {
  std::istringstream stream("test");
  b3dm::streams::BinaryFile binary_file(stream);

  ASSERT_TRUE(binary_file.Ok());
}

TEST(BinaryFileTest, Read8) {
  std::istringstream stream("abc");
  b3dm::streams::BinaryFile binary_file(stream);

  uint8_t result = binary_file.Read8();

  ASSERT_EQ(result, 'a');
}

TEST(BinaryFileTest, Read) {
  std::string const expected{"data"};
  std::istringstream stream(expected);
  b3dm::streams::BinaryFile binary_file(stream);

  std::string buf(4, 0);
  binary_file.Read(buf.data(), 4);

  ASSERT_EQ(buf, expected);
}

TEST(BinaryFileTest, Read32) {
  std::istringstream stream("\x01\x02\x03\x04", std::ios::binary);
  b3dm::streams::BinaryFile binary_file(stream);

  uint32_t result = binary_file.Read32();

  ASSERT_EQ(result, 0x04030201);
}
