//
// Created by D.Zaycev on 01.11.2023.
//

#include <iostream>

#include "b3dm-cpp/decoder.h"
#include "b3dm-cpp/file.h"

auto main() -> int
{
  auto file = std::make_unique<b3dm::binary_file>("example.b3dm");

  if (b3dm::decoder decoder(std::move(file)); decoder.read_header() && decoder.read_body()) {
    const b3dm::header* header = decoder.get_header();

    std::streamsize const gltf_bytes_length = header->byte_length - 28 - header->feature_table_json_byte_length
        - header->feature_table_binary_byte_length - header->batch_table_json_byte_length
        - header->batch_table_binary_byte_length;

    std::cout << "b3dm contains " << gltf_bytes_length << " gltf bytes\n";

    std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);

    out_file.seekp(0);
    out_file.write(decoder.get_body()->gltf_data.get(), gltf_bytes_length);
    std::cout << out_file.tellp() << " bytes written\n";
    out_file.close();

    return 0;
  }

  return 1;
}