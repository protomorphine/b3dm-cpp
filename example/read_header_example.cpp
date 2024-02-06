#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& header = decoder.get_header();

  std::cout << "b3dm.header.magic = " << header.magic << '\n';
  std::cout << "b3dm.header.version = " << header.version << '\n';
  std::cout << "b3dm.header.byte_length = " << header.byte_length << '\n';
  std::cout << "b3dm.header.feature_table_json_byte_length = " << header.feature_table_json_byte_length << '\n';
  std::cout << "b3dm.header.feature_table_binary_byte_length = " << header.feature_table_binary_byte_length << '\n';
  std::cout << "b3dm.header.batch_table_json_byte_length = " << header.batch_table_json_byte_length << '\n';
  std::cout << "b3dm.header.batch_table_binary_byte_length = " << header.batch_table_binary_byte_length << '\n';

  return 0;
}
