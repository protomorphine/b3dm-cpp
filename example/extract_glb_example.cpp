//
// Created by D.Zaycev on 01.11.2023.
//

#include <iostream>

#include "b3dm-cpp/binary_file.h"
#include "b3dm-cpp/decoder.h"

auto main() -> int {
  auto file = std::make_unique<b3dm::streams::binary_file>("example.b3dm");

  b3dm::decoder decoder(file.get());
  const b3dm::body& body = decoder.get_body();

  std::cout << "b3dm contains " << body.gltf_data.size() << " gltf bytes\n";

  std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);
  out_file.write(decoder.get_body().gltf_data.data(), static_cast<std::streamoff>(body.gltf_data.size()));

  std::cout << out_file.tellp() << " bytes written\n";
  return 0;
}