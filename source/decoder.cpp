//
// Created by Daniil on 9/25/2023.
//

#include "b3dm-cpp/decoder.h"

#include <memory>

#include "b3dm-cpp/reader_exception.h"

template <>
auto b3dm::Decoder::read(uint32_t length) const -> std::string {
  std::string buf(length, 0);
  m_file_.read(buf.data(), length);

  return buf;
}

b3dm::Decoder::Decoder(b3dm::streams::IStream& stream) : m_file_(stream) {
  read_header();
  read_body();
}

auto b3dm::Decoder::read_header() -> void {
  std::string magic(4, 0);
  if (!m_file_.read(magic.data(), 4)) {
    throw b3dm::exceptions::ReaderException{};
  }

  if (magic != constants::kB3dmMagic) {
    throw b3dm::exceptions::IncorrectFormat{};
  }

  m_header_ = std::make_unique<Header>();
  m_header_->magic = magic;
  m_header_->version = m_file_.read32();
  m_header_->byte_length = m_file_.read32();
  m_header_->feature_table_json_byte_length = m_file_.read32();
  m_header_->feature_table_binary_byte_length = m_file_.read32();
  m_header_->batch_table_json_byte_length = m_file_.read32();
  m_header_->batch_table_binary_byte_length = m_file_.read32();

  if (m_file_.ok()) {
    return;
  }

  throw b3dm::exceptions::ReaderException{};
}

auto b3dm::Decoder::read_body() -> void {
  if (!m_file_.ok() && !m_header_) {
    throw b3dm::exceptions::ReaderException{};
  }

  auto const gltf_binary_length =
      static_cast<uint32_t>(m_header_->byte_length - constants::kB3dmHeaderLength -
                            m_header_->feature_table_json_byte_length - m_header_->feature_table_binary_byte_length -
                            m_header_->batch_table_json_byte_length - m_header_->batch_table_binary_byte_length);

  auto feature_table_json = read<std::string>(m_header_->feature_table_json_byte_length);
  auto feature_table_binary = read<streams::CharBuffer>(m_header_->feature_table_binary_byte_length);
  auto batch_table_json = read<std::string>(m_header_->batch_table_json_byte_length);
  auto batch_table_binary = read<streams::CharBuffer>(m_header_->batch_table_binary_byte_length);
  auto glb_binary = read<streams::CharBuffer>(gltf_binary_length);

  if (!m_file_.ok()) {
    throw b3dm::exceptions::ReaderException{};
  }

  m_body_ = std::make_unique<Body>();
  m_body_->feature_table_json = feature_table_json;
  m_body_->feature_table = feature_table_binary;
  m_body_->batch_table_json = batch_table_json;
  m_body_->batch_table = batch_table_binary;
  m_body_->glb_data = glb_binary;
}
