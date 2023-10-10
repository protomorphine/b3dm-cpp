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

class stream
{
public:
  virtual ~stream() = default;
  // Returns true if we can read/write bytes from/into the stream
  virtual auto ok() const -> bool = 0;

  // Current position in the stream
  virtual auto tell() -> size_t = 0;

  // Jump to the given position in the stream
  virtual void seek(size_t abs_pos) = 0;

  // Returns the next byte in the stream or 0 if ok() = false
  virtual auto read8() -> uint8_t = 0;
  virtual auto read(char* buf, uint32_t size) -> bool = 0;

  // Writes one byte in the stream (or do nothing if ok() = false)
  virtual void write8(uint8_t value) = 0;
  virtual auto write(const uint8_t* buf, uint32_t size) -> bool = 0;
};

}  // namespace b3dm

#endif  // B3DM_CPP_STREAM_H_
