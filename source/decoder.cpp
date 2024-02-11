//
// Created by Daniil on 9/25/2023.
//

#include "b3dm-cpp/decoder.h"

#include <memory>

#include "b3dm-cpp/reader_exception.h"

template <>
auto b3dm::Decoder::Read(uint32_t length) const -> std::string {
  std::string buf(length, 0);
  source_.Read(buf.data(), length);

  return buf;
}

b3dm::Decoder::Decoder(b3dm::streams::IStream& stream) : source_(stream) {
  ReadHeader();
  ReadBody();
}

auto b3dm::Decoder::ReadHeader() -> void {
  std::string magic(4, 0);
  if (!source_.Read(magic.data(), 4)) {
    throw b3dm::exceptions::ReaderException{};
  }

  if (magic != constants::kB3dmMagic) {
    throw b3dm::exceptions::IncorrectFormat{};
  }

  header_ = std::make_unique<Header>();
  header_->Magic = magic;
  header_->Version = source_.Read32();
  header_->ByteLength = source_.Read32();
  header_->FeatureTableJsonByteLength = source_.Read32();
  header_->FeatureTableBinaryByteLength = source_.Read32();
  header_->BatchTableJsonByteLength = source_.Read32();
  header_->BatchTableBinaryByteLength = source_.Read32();

  if (source_.Ok()) {
    return;
  }

  throw b3dm::exceptions::ReaderException{};
}

auto b3dm::Decoder::ReadBody() -> void {
  if (!source_.Ok() && !header_) {
    throw b3dm::exceptions::ReaderException{};
  }

  auto const gltf_binary_length =
      static_cast<uint32_t>(header_->ByteLength - constants::kB3dmHeaderLength -
                            header_->FeatureTableJsonByteLength - header_->FeatureTableBinaryByteLength -
                            header_->BatchTableJsonByteLength - header_->BatchTableBinaryByteLength);

  auto feature_table_json = Read<std::string>(header_->FeatureTableJsonByteLength);
  auto feature_table_binary = Read<streams::CharBuffer>(header_->FeatureTableBinaryByteLength);
  auto batch_table_json = Read<std::string>(header_->BatchTableJsonByteLength);
  auto batch_table_binary = Read<streams::CharBuffer>(header_->BatchTableBinaryByteLength);
  auto glb_binary = Read<streams::CharBuffer>(gltf_binary_length);

  if (!source_.Ok()) {
    throw b3dm::exceptions::ReaderException{};
  }

  body_ = std::make_unique<Body>();
  body_->FeatureTableJson = feature_table_json;
  body_->feature_table = feature_table_binary;
  body_->BatchTableJson = batch_table_json;
  body_->BatchTable = batch_table_binary;
  body_->GlbData = glb_binary;
}
