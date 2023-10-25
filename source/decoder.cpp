//
// Created by Daniil on 9/25/2023.
//

#include <memory>

#include "b3dm-cpp/decoder.h"

b3dm::decoder::decoder(file_stream* file_interface)
    : m_file(file_interface)
{
}

auto b3dm::decoder::read_header() -> bool
{
  std::string magic;
  if (!m_file->read_string(4, magic)) {
    return false;
  }

  if (magic != b3dm_magic) {
    return false;
  }

  m_header = header {magic,
                     m_file->read32(),
                     m_file->read32(),
                     m_file->read32(),
                     m_file->read32(),
                     m_file->read32(),
                     m_file->read32()};

  return m_file->ok();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-c-arrays"
auto b3dm::decoder::read_body() -> bool
{
  if (!m_file->ok()) {
    return false;
  }

  size_t const feature_table_json_length =
      m_header.feature_table_json_byte_length;

  size_t const feature_table_binary_length =
      m_header.feature_table_binary_byte_length;

  size_t const batch_table_json_length = m_header.batch_table_json_byte_length;

  size_t const batch_table_binary_length =
      m_header.batch_table_binary_byte_length;

  size_t const gltf_binary_length = (m_header.byte_length - b3dm_header_length)
      - feature_table_json_length - feature_table_binary_length
      - batch_table_json_length - batch_table_binary_length;

  std::string feature_table_json;
  m_file->read_string(feature_table_json_length, feature_table_json);
  auto feature_table_binary =
      std::make_unique<uint8_t[]>(feature_table_binary_length);
  m_file->read(feature_table_binary.get(), feature_table_binary_length);

  std::string batch_table_json;
  m_file->read_string(batch_table_json_length, batch_table_json);
  auto batch_table_binary =
      std::make_unique<uint8_t[]>(batch_table_binary_length);
  m_file->read(batch_table_binary.get(), batch_table_binary_length);

  auto gltf_binary = std::make_unique<uint8_t[]>(gltf_binary_length);
  m_file->read(gltf_binary.get(), gltf_binary_length);

  if (!m_file->ok()) {
    return false;
  }

  m_body = body {feature_table_json,
                 feature_table_binary.get(),
                 batch_table_json,
                 batch_table_binary.get(),
                 gltf_binary.get()};

  return m_file->ok();
}
#pragma clang diagnostic pop
