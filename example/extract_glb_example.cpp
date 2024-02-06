//
// Created by D.Zaycev on 01.11.2023.
//

#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& body = decoder.get_body();

  std::cout << "b3dm contains " << body.glb_data.size() << " gltf bytes\n";

  std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);
  out_file.write(decoder.get_body().glb_data.data(), static_cast<std::streamoff>(body.glb_data.size()));

  std::cout << out_file.tellp() << " bytes written\n";
  return 0;
}