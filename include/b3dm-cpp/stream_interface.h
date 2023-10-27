//
// Created by Daniil on 9/25/2023.
//

#ifndef B3DM_CPP_STREAM_H_
#define B3DM_CPP_STREAM_H_

#include <cstddef>
#include <cstdint>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

namespace b3dm
{

/// @brief read-only stream interface.
class B3DM_CPP_EXPORT stream
{
public:
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
  virtual auto read8() -> uint8_t = 0;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if read succeed, otherwise - false.
  virtual auto read(uint8_t * buf, uint32_t size) -> bool = 0;
};

}  // namespace b3dm

#endif  // B3DM_CPP_STREAM_H_
