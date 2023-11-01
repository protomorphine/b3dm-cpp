//
// Created by D.Zaycev on 25.10.2023.
//
#include <iostream>

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  auto raw_file = std::make_unique<std::ifstream>("example.b3dm", std::ios::binary);
  auto file = std::make_unique<b3dm::file_stream>(std::move(raw_file));
  b3dm::decoder decoder(std::move(file));

  if (decoder.read_header() && decoder.read_body()) {
    const auto *body = decoder.get_body();

    std::cout << "b3dm.body.feature_table_json = " + body->feature_table_json << '\n';
    std::cout << "b3dm.body.batch_table_json = " + body->batch_table_json << '\n';

    return 0;
  }

  std::cout << "could not read b3dm" << '\n';
  return 0;
}