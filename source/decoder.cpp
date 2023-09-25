//
// Created by Daniil on 9/25/2023.
//

#include "b3dm-cpp/decoder.h"

b3dm::decoder::decoder(file_stream* file_interface)
    : m_file(file_interface)
{
}

auto b3dm::decoder::read_header() -> bool
{
  uint32_t const magic = m_file->read32();
  uint32_t const version = m_file->read32();
  uint32_t const byte_length = m_file->read32();
  uint32_t const feature_table_json_byte_length = m_file->read32();
  uint32_t const feature_table_binary_byte_length = m_file->read32();
  uint32_t const batch_table_json_byte_length = m_file->read32();
  uint32_t const batch_table_binary_byte_length = m_file->read32();

  if (magic != b3dm_magic) {
    throw std::runtime_error("header magic number invalid");
  }

  file_header header{};

  header.magic = magic;
  header.version = version;
  header.byte_length = byte_length;
  header.feature_table_binary_byte_length = feature_table_json_byte_length;
  header.feature_table_binary_byte_length = feature_table_binary_byte_length;
  header.feature_table_json_byte_length = batch_table_json_byte_length;
  header.batch_table_binary_byte_length = batch_table_binary_byte_length;

  m_header = header;
  return true;
}

auto b3dm::decoder::read_body() -> bool
{
  file_body const body{};

  m_body = body;
  return true;
}
