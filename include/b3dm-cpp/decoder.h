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
/// @brief b3dm magic identifier.
constexpr std::string_view kB3dmMagic = "b3dm";

/// @brief b3dm header length.
constexpr size_t kB3dmHeaderLength = 28;
}  // namespace constants

/// @brief b3dm header.
struct Header {
  std::string magic;
  uint32_t version;
  uint32_t byte_length;
  uint32_t feature_table_json_byte_length;
  uint32_t feature_table_binary_byte_length;
  uint32_t batch_table_json_byte_length;
  uint32_t batch_table_binary_byte_length;
};

/// @brief b3dm body.
struct Body {
  std::string feature_table_json;
  b3dm::streams::CharBuffer feature_table;

  std::string batch_table_json;
  b3dm::streams::CharBuffer batch_table;

  b3dm::streams::CharBuffer glb_data;
};

/// @brief b3dm decoder. Allows to read data from b3dm file.
class B3DM_CPP_EXPORT Decoder {
 public:
  explicit Decoder(b3dm::streams::IStream& stream);

  /// @brief Getter for b3dm header.
  /// @return Header.
  auto get_header() const -> const Header& { return *m_header_; }

  /// @brief Getter for b3dm body.
  /// @return Body.
  auto get_body() const -> const Body& { return *m_body_; }

 private:
  /// @brief Reads header from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_header() -> void;

  /// @brief Reads body from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_body() -> void;

  template <typename BufferType>
  auto read(uint32_t length) const -> BufferType {
    BufferType buf(length);
    m_file_.read(buf.data(), length);

    return buf;
  }


  b3dm::streams::IStream& m_file_;

  std::unique_ptr<Header> m_header_ = nullptr;
  std::unique_ptr<Body> m_body_ = nullptr;
};

}  // namespace b3dm