//
// Created by Daniil on 9/25/2023.
//

#pragma once

#include <cstdint>
#include <fstream>
#include <memory>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

#include "binary_readonly_stream.h"
#include "format_exception.h"

namespace b3dm
{

namespace constants
{
/// @brief b3dm magic identifier.
constexpr std::string_view b3dm_magic = "b3dm";

/// @brief b3dm header length.
constexpr size_t b3dm_header_length = 28;
}  // namespace constants

/// @brief b3dm header.
struct header
{
  std::string magic;
  uint32_t version;
  uint32_t byte_length;
  uint32_t feature_table_json_byte_length;
  uint32_t feature_table_binary_byte_length;
  uint32_t batch_table_json_byte_length;
  uint32_t batch_table_binary_byte_length;
};

/// @brief b3dm body.
struct body
{
  std::string feature_table_json;
  b3dm::streams::char_buffer feature_table;

  std::string batch_table_json;
  b3dm::streams::char_buffer batch_table;

  b3dm::streams::char_buffer gltf_data;
};

/// @brief b3dm decoder. Allows to read data from b3dm file.
class B3DM_CPP_EXPORT decoder
{
public:
  explicit decoder(b3dm::streams::binary_readonly_stream* stream);

  /// @brief Getter for b3dm header.
  /// @return Header.
  auto get_header() const -> const header& { return *m_header; }

  /// @brief Getter for b3dm body.
  /// @return Body.
  auto get_body() const -> const body& { return *m_body; }

private:
  /// @brief Reads header from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_header() -> void;

  /// @brief Reads body from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_body() -> void;

  b3dm::streams::binary_readonly_stream* m_file;

  std::unique_ptr<header> m_header = nullptr;
  std::unique_ptr<body> m_body     = nullptr;
};

}  // namespace b3dm