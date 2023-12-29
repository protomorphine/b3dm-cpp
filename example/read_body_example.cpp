//
// Created by D.Zaycev on 25.10.2023.
//
#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  auto file = std::make_unique<b3dm::streams::binary_file>("example.b3dm");

  b3dm::decoder const decoder(file.get());
  const b3dm::body& body = decoder.get_body();

  std::cout << "b3dm.body.feature_table_json = " << body.feature_table_json << '\n';
  std::cout << "b3dm.body.batch_table_json = " << body.batch_table_json << '\n';

  return 0;
}