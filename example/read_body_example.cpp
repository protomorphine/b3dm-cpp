//
// Created by D.Zaycev on 25.10.2023.
//
#include <iostream>

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  std::ifstream basic_stream("example.b3dm", std::fstream::binary);
  b3dm::file_stream file(&basic_stream);

  b3dm::decoder decoder(&file);

  if (decoder.read_header() && decoder.read_body()) {
    auto const body = decoder.get_body();

    std::cout << "b3dm.body.feature_table_json = " + body.feature_table_json << '\n';
    std::cout << "b3dm.body.batch_table_json = " + body.batch_table_json << '\n';

    return 0;
  }

  std::cout << "could not read b3dm" << '\n';
  return 1;
}