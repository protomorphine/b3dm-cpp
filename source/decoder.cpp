//
// Created by Daniil on 9/25/2023.
//

#include <memory>

#include "b3dm-cpp/decoder.h"

b3dm::decoder::decoder(b3dm::streams::binary_readonly_stream* file_interface)
    : m_file(file_interface)
{
  read_header();
  read_body();
}

auto b3dm::decoder::read_header() -> void
{
  std::string magic;
  if (!m_file->read(magic.data(), 4)) {
    throw std::system_error();
  }

  if (magic != b3dm_magic) {
    throw std::system_error();
  }

  m_header = {.magic = magic,
              .version = m_file->read32(),
              .byte_length = m_file->read32(),
              .feature_table_json_byte_length = m_file->read32(),
              .feature_table_binary_byte_length = m_file->read32(),
              .batch_table_json_byte_length = m_file->read32(),
              .batch_table_binary_byte_length = m_file->read32()};

  if (m_file->ok()) {
    return;
  }

  throw std::system_error();
}

auto b3dm::decoder::read_body() -> void
{
  if (!m_file->ok() && ((&m_header) != nullptr)) {
    throw std::system_error();
  }

  size_t const feature_table_json_length = m_header.feature_table_json_byte_length;
  size_t const feature_table_binary_length = m_header.feature_table_binary_byte_length;
  size_t const batch_table_json_length = m_header.batch_table_json_byte_length;
  size_t const batch_table_binary_length = m_header.batch_table_binary_byte_length;

  size_t const gltf_binary_length = (m_header.byte_length - b3dm_header_length) - feature_table_json_length
      - feature_table_binary_length - batch_table_json_length - batch_table_binary_length;

  std::string feature_table_json;
  m_file->read(feature_table_json.data(), feature_table_json_length);
  auto feature_table_binary = m_file->read(feature_table_binary_length);

  std::string batch_table_json;
  m_file->read(batch_table_json.data(), batch_table_json_length);
  auto batch_table_binary = m_file->read(batch_table_binary_length);

  auto gltf_binary = m_file->read(gltf_binary_length);

  if (!m_file->ok()) {
    throw std::system_error();
  }

  m_body = {.feature_table_json = feature_table_json,
            .feature_table = std::move(feature_table_binary),
            .batch_table_json = batch_table_json,
            .batch_table = std::move(batch_table_binary),
            .gltf_data = std::move(gltf_binary)};

  if (m_file->ok()) {
    return;
  }

  throw std::system_error();
}
