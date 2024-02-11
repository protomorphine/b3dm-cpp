#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& header = decoder.GetHeader();

  std::cout << "b3dm.header.Magic = " << header.Magic << '\n';
  std::cout << "b3dm.header.version = " << header.Version << '\n';
  std::cout << "b3dm.header.ByteLength = " << header.ByteLength << '\n';
  std::cout << "b3dm.header.FeatureTableJsonByteLength = " << header.FeatureTableJsonByteLength << '\n';
  std::cout << "b3dm.header.FeatureTableBinaryByteLength = " << header.FeatureTableBinaryByteLength << '\n';
  std::cout << "b3dm.header.BatchTableJsonByteLength = " << header.BatchTableJsonByteLength << '\n';
  std::cout << "b3dm.header.BatchTableBinaryByteLength = " << header.BatchTableBinaryByteLength << '\n';

  return 0;
}
