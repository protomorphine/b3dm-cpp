//
// Created by D.Zaycev on 26.09.2023.
//

#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>

#include "b3dm-cpp/stream_interface.h"

namespace b3dm::streams
{

/// @brief wrapper for ifstream
/// @see ifstream
class B3DM_CPP_EXPORT binary_file : public binary_readonly_stream
{
public:
  explicit binary_file(const std::filesystem::path& file_name);

  /// @brief is file_stream in ok state.
  /// @return true - if file_stream in ok state, otherwise - false.
  auto ok() const -> bool override { return m_ok; }

  /// @brief gets current stream position.
  /// @return ifstream position.
  auto tell() -> size_t override { return m_file->tellg(); }

  /// @brief goes to position.
  /// @param[in] abs_pos position to set.
  auto seek(size_t abs_pos) -> void override { m_file->seekg(static_cast<std::streamoff>(abs_pos)); }

  /// @brief reads 1 byte from stream.
  /// @return byte.
  auto read8() -> unsigned char override;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if read succeed, otherwise - false.
  auto read(char* buf, size_t size) -> bool override;

  /// @brief read 4 bytes, and concatenate them in int32.
  /// @return int32.
  auto read32() -> unsigned int override;

private:
  std::unique_ptr<std::ifstream> m_file;
  bool m_ok = true;
};

}  // namespace b3dm::streams
