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
  auto magic_buf = std::make_unique<uint8_t[]>(4 + 1);
  m_file->read(magic_buf.get(), 4);

  std::string const magic = reinterpret_cast<const char*>(magic_buf.get());
  uint32_t const version = m_file->read32();
  uint32_t const byte_length = m_file->read32();
  uint32_t const feature_table_json_byte_length = m_file->read32();
  uint32_t const feature_table_binary_byte_length = m_file->read32();
  uint32_t const batch_table_json_byte_length = m_file->read32();
  uint32_t const batch_table_binary_byte_length = m_file->read32();

  if (magic != b3dm_magic) {
    return false;
  }

  header header;
  header.magic = magic;
  header.version = version;
  header.byte_length = byte_length;
  header.feature_table_json_byte_length = feature_table_json_byte_length;
  header.feature_table_binary_byte_length = feature_table_binary_byte_length;
  header.batch_table_json_byte_length = batch_table_json_byte_length;
  header.batch_table_binary_byte_length = batch_table_binary_byte_length;

  m_header = header;
  return m_file->ok();
}

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

  auto feature_table_json =
      std::make_unique<uint8_t[]>(feature_table_json_length + 1);

  auto feature_table_binary =
      std::make_unique<uint8_t[]>(feature_table_binary_length + 1);

  auto batch_table_json =
      std::make_unique<uint8_t[]>(batch_table_json_length + 1);

  auto batch_table_binary =
      std::make_unique<uint8_t[]>(batch_table_binary_length + 1);

  if (!m_file->read(feature_table_json.get(), feature_table_json_length)) {
    return false;
  }

  if (!m_file->read(feature_table_binary.get(), feature_table_binary_length)) {
    return false;
  }

  if (!m_file->read(batch_table_json.get(), batch_table_json_length)) {
    return false;
  }

  if (!m_file->read(batch_table_binary.get(), batch_table_binary_length)) {
    return false;
  }

  // body const body {};

  m_body = body {
      reinterpret_cast<const char*>(feature_table_json.get()),
      feature_table_binary.get(),
      reinterpret_cast<const char*>(batch_table_json.get()),
      batch_table_json.get()
  };

  return m_file->ok();
}
