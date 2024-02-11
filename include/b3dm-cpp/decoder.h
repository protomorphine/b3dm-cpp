//
// Created by Daniil on 9/25/2023.
//

#pragma once

#include <b3dm-cpp/b3dm-cpp_export.hpp>
#include <cstdint>
#include <fstream>
#include <memory>

#include "format_exception.h"
#include "stream.h"

namespace b3dm {

namespace constants {
/// @brief b3dm Magic identifier.
constexpr std::string_view kB3dmMagic = "b3dm";

/// @brief b3dm header length.
constexpr size_t kB3dmHeaderLength = 28;
}  // namespace constants

/// @brief b3dm header.
struct Header {
  std::string Magic;
  uint32_t Version;
  uint32_t ByteLength;
  uint32_t FeatureTableJsonByteLength;
  uint32_t FeatureTableBinaryByteLength;
  uint32_t BatchTableJsonByteLength;
  uint32_t BatchTableBinaryByteLength;
};

/// @brief b3dm body.
struct Body {
  std::string FeatureTableJson;
  b3dm::streams::CharBuffer feature_table;

  std::string BatchTableJson;
  b3dm::streams::CharBuffer BatchTable;

  b3dm::streams::CharBuffer GlbData;
};

/// @brief b3dm decoder. Allows to Read data from b3dm file.
class B3DM_CPP_EXPORT Decoder {
 public:
  explicit Decoder(b3dm::streams::IStream& stream);

  /// @brief Getter for b3dm header.
  /// @return Header.
  auto GetHeader() const -> const Header& { return *header_; }

  /// @brief Getter for b3dm body.
  /// @return Body.
  auto GetBody() const -> const Body& { return *body_; }

 private:
  /// @brief Reads header from file_stream.
  /// @return true - if Read succeed, otherwise - false.
  auto ReadHeader() -> void;

  /// @brief Reads body from file_stream.
  /// @return true - if Read succeed, otherwise - false.
  auto ReadBody() -> void;

  template <typename BufferType>
  auto Read(uint32_t length) const -> BufferType {
    BufferType buf(length);
    source_.Read(buf.data(), length);

    return buf;
  }


  b3dm::streams::IStream& source_;

  std::unique_ptr<Header> header_ = nullptr;
  std::unique_ptr<Body> body_ = nullptr;
};

}  // namespace b3dm