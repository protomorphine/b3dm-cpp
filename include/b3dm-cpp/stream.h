//
// Created by Daniil on 9/25/2023.
//

#pragma once

#include <b3dm-cpp/b3dm-cpp_export.hpp>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace b3dm::streams {

using CharBuffer = std::vector<char>;

/// @brief Read-only stream interface.
class B3DM_CPP_EXPORT IStream {
 protected:
  IStream() = default;
  IStream(const IStream&) = default;
  IStream(IStream&&) = default;

 public:
  virtual ~IStream() = default;

 protected:
  auto operator=(const IStream&) -> IStream& = default;
  auto operator=(IStream&&) -> IStream& = default;

 public:
  /// @brief is file_stream in Ok state.
  /// @return true - if file_stream in Ok state, otherwise - false.
  virtual auto Ok() const -> bool = 0;

  /// @brief reads 1 byte from stream.
  /// @return byte.
  virtual auto Read8() -> uint8_t = 0;

  /// @brief Read 4 bytes, and concatenate them in int32.
  /// @return int32.
  virtual auto Read32() -> uint32_t = 0;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if Read succeed, otherwise - false.
  virtual auto Read(char* buf, size_t size) -> bool = 0;
};

}  // namespace b3dm::streams
