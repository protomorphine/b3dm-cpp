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
  const auto& body = decoder.GetBody();

  std::cout << "b3dm.body.FeatureTableJson = " << body.FeatureTableJson << '\n';
  std::cout << "b3dm.body.BatchTableJson = " << body.BatchTableJson << '\n';

  return 0;
}