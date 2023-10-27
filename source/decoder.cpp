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

auto b3dm::decoder::read_body() -> bool
{
  if (!m_file->ok()) {
    return false;
  }

  size_t const feature_table_json_length = m_header.feature_table_json_byte_length;
  size_t const feature_table_binary_length = m_header.feature_table_binary_byte_length;
  size_t const batch_table_json_length = m_header.batch_table_json_byte_length;
  size_t const batch_table_binary_length = m_header.batch_table_binary_byte_length;

  size_t const gltf_binary_length = (m_header.byte_length - b3dm_header_length)
      - feature_table_json_length - feature_table_binary_length
      - batch_table_json_length - batch_table_binary_length;

  std::string feature_table_json;
  m_file->read_string(feature_table_json_length, feature_table_json);
  auto feature_table_binary = m_file->read(feature_table_binary_length);

  std::string batch_table_json;
  m_file->read_string(batch_table_json_length, batch_table_json);
  auto batch_table_binary = m_file->read(batch_table_binary_length);

  auto gltf_binary = m_file->read(gltf_binary_length);

  if (!m_file->ok()) {
    return false;
  }

  body body{};
  body.feature_table_json = feature_table_json;
  body.feature_table = std::move(feature_table_binary);
  body.batch_table_json = batch_table_json;
  body.batch_table = std::move(batch_table_binary);
  body.gltf_data = std::move(gltf_binary);

  m_body = std::move(body);

  return m_file->ok();
}
