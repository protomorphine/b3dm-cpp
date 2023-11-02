//
// Created by Daniil on 9/25/2023.
//

#ifndef B3DM_CPP_SOURCE_DECODER_H_  // NOLINT(*-identifier-naming)
#define B3DM_CPP_SOURCE_DECODER_H_

#include <cstdint>
#include <fstream>
#include <memory>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

#include "stream_interface.h"

namespace b3dm
{

/// @brief b3dm magic identifier.
constexpr std::string_view b3dm_magic = "b3dm";

/// @brief b3dm header length.
constexpr size_t b3dm_header_length = 28;

/// @brief b3dm header.
struct header
{
  std::string magic;
  int version;
  int byte_length;
  int feature_table_json_byte_length;
  int feature_table_binary_byte_length;
  int batch_table_json_byte_length;
  int batch_table_binary_byte_length;
};

/// @brief b3dm body.
struct body
{
  std::string feature_table_json;
  std::unique_ptr<char_buffer> feature_table;

  std::string batch_table_json;
  std::unique_ptr<char_buffer> batch_table;

  std::unique_ptr<char_buffer> gltf_data;
};

/// @brief b3dm decoder. Allows to read data from b3dm file.
class B3DM_CPP_EXPORT decoder
{
public:
  explicit decoder(std::unique_ptr<stream> file_interface);

  /// @brief Getter for b3dm header.
  /// @return Header.
  auto get_header() const -> const header* { return &m_header; }

  /// @brief Getter for b3dm body.
  /// @return Body.
  auto get_body() const -> const body* { return &m_body; }

  /// @brief Reads header from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_header() -> bool;

  /// @brief Reads body from file_stream.
  /// @return true - if read succeed, otherwise - false.
  auto read_body() -> bool;

private:
  std::unique_ptr<stream> m_stream;
  header m_header;
  body m_body;
};

}  // namespace b3dm

#endif  // B3DM_CPP_SOURCE_DECODER_H_
