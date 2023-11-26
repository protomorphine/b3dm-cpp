//
// Created by Daniil on 9/25/2023.
//

#include <memory>

#include "b3dm-cpp/decoder.h"

#include "b3dm-cpp/reader_exception.h"

b3dm::decoder::decoder(b3dm::streams::binary_readonly_stream* file_interface)
    : m_file(file_interface)
{
  read_header();
  read_body();
}

auto b3dm::decoder::read_header() -> void
{
  std::string magic(4, 0);
  if (!m_file->read(magic.data(), 4)) {
    throw b3dm::exceptions::reader_exception();
  }

  if (magic != constants::b3dm_magic) {
    throw b3dm::exceptions::incorrect_format();
  }

  m_header = std::make_unique<header>();
  m_header->magic = magic;
  m_header->version = m_file->read32();
  m_header->byte_length = m_file->read32();
  m_header->feature_table_json_byte_length = m_file->read32();
  m_header->feature_table_binary_byte_length = m_file->read32();
  m_header->batch_table_json_byte_length = m_file->read32();
  m_header->batch_table_binary_byte_length = m_file->read32();

  if (m_file->ok()) {
    return;
  }

  throw b3dm::exceptions::reader_exception();
}

auto b3dm::decoder::read_body() -> void
{
  if (!m_file->ok() && !m_header) {
    throw b3dm::exceptions::reader_exception();
  }

  uint32_t const gltf_binary_length = m_header->byte_length - constants::b3dm_header_length
      - m_header->feature_table_json_byte_length - m_header->feature_table_binary_byte_length
      - m_header->batch_table_json_byte_length - m_header->batch_table_binary_byte_length;

  std::string feature_table_json(m_header->feature_table_json_byte_length, 0);
  m_file->read(feature_table_json.data(), m_header->feature_table_json_byte_length);

  b3dm::streams::char_buffer feature_table_binary(m_header->feature_table_binary_byte_length);
  m_file->read(feature_table_binary.data(), m_header->feature_table_binary_byte_length);

  std::string batch_table_json(m_header->batch_table_json_byte_length, 0);
  m_file->read(batch_table_json.data(), m_header->batch_table_json_byte_length);

  b3dm::streams::char_buffer batch_table_binary(m_header->batch_table_binary_byte_length);
  m_file->read(batch_table_binary.data(), m_header->batch_table_binary_byte_length);

  b3dm::streams::char_buffer gltf_binary(gltf_binary_length);
  m_file->read(gltf_binary.data(), gltf_binary_length);

  if (!m_file->ok()) {
    throw b3dm::exceptions::reader_exception();
  }

  m_body = std::make_unique<body>();
  m_body->feature_table_json = feature_table_json;
  m_body->feature_table = feature_table_binary;
  m_body->batch_table_json = batch_table_json;
  m_body->batch_table = batch_table_binary;
  m_body->gltf_data = gltf_binary;
}
