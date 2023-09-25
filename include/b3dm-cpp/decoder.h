//
// Created by Daniil on 9/25/2023.
//

#ifndef B3DM_CPP_SOURCE_DECODER_H_
#define B3DM_CPP_SOURCE_DECODER_H_

#include <cstdint>

class file_interface
{
public:
  virtual ~file_interface() = default;

  // Returns true if we can read/write bytes from/into the file
  virtual auto ok() const -> bool = 0;

  // Current position in the file
  virtual auto tell() -> size_t = 0;

  // Jump to the given position in the file
  virtual void seek(size_t abs_pos) = 0;

  // Returns the next byte in the file or 0 if ok() = false
  virtual auto read8() -> uint8_t = 0;
  virtual auto read(uint8_t* buf, uint32_t size) -> bool = 0;

  // Writes one byte in the file (or do nothing if ok() = false)
  virtual void write8(uint8_t value) = 0;
  virtual auto write(const uint8_t* buf, uint32_t size) -> bool = 0;
};

class decoder
{
public:
  decoder(file_interface* file_interface, void* decoder_delegate);

  auto readHeader() -> bool;
  auto readBody() -> bool;

private:
  file_interface* m_file;
};

#endif  // B3DM_CPP_SOURCE_DECODER_H_
