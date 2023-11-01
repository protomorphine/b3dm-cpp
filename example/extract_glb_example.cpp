//
// Created by D.Zaycev on 01.11.2023.
//

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  auto file = std::make_unique<b3dm::file_stream>("example.b3dm");
  b3dm::decoder decoder(std::move(file));

  if (decoder.read_header() && decoder.read_body()) {
    const auto* header = decoder.get_header();
    std::streamsize const glb_length = header->byte_length - 28
        - header->feature_table_json_byte_length
        - header->feature_table_binary_byte_length
        - header->batch_table_json_byte_length
        - header->batch_table_binary_byte_length;

    std::ofstream out_file("example.glb",
                           std::ios::out | std::ios::binary | std::ios::app);
    char* data = decoder.get_body()->gltf_data.get();
    out_file.write(data, glb_length);

    return 0;
  }

  return 1;
}