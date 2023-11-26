//
// Created by Daniil on 9/25/2023.
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

namespace b3dm::streams
{

using char_buffer = std::vector<char>;

/// @brief read-only stream interface.
class B3DM_CPP_EXPORT binary_readonly_stream
{
public:
  virtual ~binary_readonly_stream() = default;

  /// @brief is file_stream in ok state.
  /// @return true - if file_stream in ok state, otherwise - false.
  virtual auto ok() const -> bool = 0;

  /// @brief gets current stream position.
  /// @return ifstream position.
  virtual auto tell() -> size_t = 0;

  /// @brief goes to position.
  /// @param[in] abs_pos position to set.
  virtual void seek(size_t abs_pos) = 0;

  /// @brief reads 1 byte from stream.
  /// @return byte.
  virtual auto read8() -> unsigned char = 0;

  /// @brief read 4 bytes, and concatenate them in int32.
  /// @return int32.
  virtual auto read32() -> unsigned int = 0;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if read succeed, otherwise - false.
  virtual auto read(char* buf, size_t size) -> bool = 0;
};

}  // namespace b3dm::streams
