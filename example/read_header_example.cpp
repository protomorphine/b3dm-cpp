#include <iostream>

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  std::ifstream basic_stream("example.b3dm", std::ios::binary);
  b3dm::file_stream file(&basic_stream);

  b3dm::decoder decoder(&file);

  if (decoder.read_header()) {
    auto const header = decoder.get_header();

    std::cout << "b3dm.header.magic = " + header.magic << '\n';
    std::cout << "b3dm.header.version = " << header.version << '\n';
    std::cout << "b3dm.header.byte_length = " << header.byte_length << '\n';

    std::cout << "b3dm.header.feature_table_json_byte_length = "
              << header.feature_table_json_byte_length << '\n';

    std::cout << "b3dm.header.feature_table_binary_byte_length = "
              << header.feature_table_binary_byte_length << '\n';

    std::cout << "b3dm.header.batch_table_json_byte_length = "
              << header.batch_table_json_byte_length << '\n';

    std::cout << "b3dm.header.batch_table_binary_byte_length = "
              << header.batch_table_binary_byte_length << '\n';

    return 0;
  }

  std::cout << "could not read b3dm header" << '\n';
  return 1;
}
