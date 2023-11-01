#include <iostream>

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  auto raw_file = std::make_unique<std::ifstream>("example.b3dm", std::ios::binary);
  auto file = std::make_unique<b3dm::file_stream>(std::move(raw_file));
  b3dm::decoder decoder(std::move(file));

  if (decoder.read_header()) {
    const auto *const header = decoder.get_header();

    std::cout << "b3dm.header.magic = " + header->magic << '\n';
    std::cout << "b3dm.header.version = " << header->version << '\n';
    std::cout << "b3dm.header.byte_length = " << header->byte_length << '\n';

    std::cout << "b3dm.header.feature_table_json_byte_length = "
              << header->feature_table_json_byte_length << '\n';

    std::cout << "b3dm.header.feature_table_binary_byte_length = "
              << header->feature_table_binary_byte_length << '\n';

    std::cout << "b3dm.header.batch_table_json_byte_length = "
              << header->batch_table_json_byte_length << '\n';

    std::cout << "b3dm.header.batch_table_binary_byte_length = "
              << header->batch_table_binary_byte_length << '\n';

    return 0;
  }

  std::cout << "could not read b3dm header" << '\n';
  return 1;
}
