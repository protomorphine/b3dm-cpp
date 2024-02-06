//
// Created by D.Zaycev on 25.10.2023.
//
#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& body = decoder.get_body();

  std::cout << "b3dm.body.feature_table_json = " << body.feature_table_json << '\n';
  std::cout << "b3dm.body.batch_table_json = " << body.batch_table_json << '\n';

  return 0;
}