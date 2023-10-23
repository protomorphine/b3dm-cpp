//
// Created by D.Zaycev on 26.09.2023.
//

#ifndef B3DM_CPP_SOURCE_FILESTREAM_H_
#define B3DM_CPP_SOURCE_FILESTREAM_H_

#include <fstream>

#include "b3dm-cpp/stream_interface.h"

namespace b3dm
{

class B3DM_CPP_EXPORT file_stream : public stream
{
public:
  ~file_stream() override = default;

  explicit file_stream(std::ifstream* stream);

  // Returns true if we can read/write bytes from/into the stream
  auto ok() const -> bool override { return m_ok; }

  // Current position in the stream
  auto tell() -> size_t override;

  // Jump to the given position in the stream
  void seek(size_t abs_pos) override;

  // Returns the next byte in the stream or 0 if ok() = false
  auto read8() -> uint8_t override;

  // Returns the next 4 bytes from stream or 0 if ok() = false
  auto read32() -> uint32_t;

  // Reads 'size' bytes in 'buf'
  auto read(uint8_t * buf, uint32_t size) -> bool override;

  // Writes one byte in the stream (or do nothing if ok() = false)
  void write8(uint8_t value) override;
  auto write(const uint8_t* buf, uint32_t size) -> bool override;

private:
  std::ifstream* m_file;
  bool m_ok;
};

}  // namespace b3dm

#endif  // B3DM_CPP_SOURCE_FILESTREAM_H_
