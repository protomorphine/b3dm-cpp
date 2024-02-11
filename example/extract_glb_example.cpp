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
  const auto& body = decoder.GetBody();

  std::cout << "b3dm contains " << body.GlbData.size() << " gltf bytes\n";

  std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);
  out_file.write(decoder.GetBody().GlbData.data(), static_cast<std::streamoff>(body.GlbData.size()));

  std::cout << out_file.tellp() << " bytes written\n";
  return 0;
}