//
// Created by D.Zaycev on 26.09.2023.
//

#ifndef B3DM_CPP_SOURCE_FILESTREAM_H_
#define B3DM_CPP_SOURCE_FILESTREAM_H_

#include <fstream>

#include "b3dm-cpp/stream_interface.h"

namespace b3dm
{

/// @brief abstraction wrapper for ifstream
/// @see ifstream
class B3DM_CPP_EXPORT file_stream : public stream
{
public:
  explicit file_stream(std::ifstream* stream);

  /// @brief is file_stream in ok state.
  /// @return true - if file_stream in ok state, otherwise - false.
  auto ok() const -> bool override { return m_ok; }

  /// @brief gets current stream position.
  /// @return ifstream position.
  auto tell() -> size_t override { return m_file->tellg(); }

  /// @brief goes to position.
  /// @param[in] abs_pos position to set.
  void seek(size_t abs_pos) override { m_file->seekg(abs_pos); }

  /// @brief reads 1 byte from stream.
  /// @return byte.
  auto read8() -> uint8_t override;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if read succeed, otherwise - false.
  auto read(uint8_t * buf, uint32_t size) -> bool override;

  /// @brief read 4 bytes, and concatenate them in int32.
  /// @return int32.
  auto read32() -> uint32_t;

  /// @brief reads string from stream.
  /// @param[in] size size of string.
  /// @param[out] out_string read string.
  /// @return true - if read succeed, otherwise - false.
  auto read_string(size_t size, std::string& out_string) -> bool;

  /// @brief reads binary data.
  /// @param[in] size length of data.
  /// @return unique pointer to data.
  auto read(size_t size) -> std::unique_ptr<uint8_t[]>;

private:
  std::ifstream* m_file;
  bool m_ok;
};

}  // namespace b3dm

#endif  // B3DM_CPP_SOURCE_FILESTREAM_H_
