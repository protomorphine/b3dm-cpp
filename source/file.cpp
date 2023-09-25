//
// Created by D.Zaycev on 26.09.2023.
//

#include <memory>

#include "b3dm-cpp/file.h"

b3dm::file_stream::file_stream(std::ifstream* stream)
    : m_file(stream)
    , m_ok(true)
{
}

auto b3dm::file_stream::read8() -> uint8_t
{
  if (m_file->good()) {
    auto val = std::make_unique<char>(sizeof(uint8_t) + 1);
    m_file->read(val.get(), sizeof(uint8_t));

    return *val;
  }

  m_ok = false;
  return 0;
}

auto b3dm::file_stream::read(char* buf, uint32_t size) -> bool
{
  m_file->read(buf, size);
  return m_file->gcount() == size;
}

void b3dm::file_stream::seek(size_t abs_pos)
{
  m_file->seekg(abs_pos);
}

auto b3dm::file_stream::tell() -> size_t
{
  return m_file->tellg();
}

auto b3dm::file_stream::read32() -> uint32_t
{
  uint8_t const byte1 = read8();
  uint8_t const byte2 = read8();
  uint8_t const byte3 = read8();
  uint8_t const byte4 = read8();

  if (ok()) {
    return ((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4);
  }

  return 0;
}
void b3dm::file_stream::write8(uint8_t value) {}

auto b3dm::file_stream::write(const uint8_t* buf, uint32_t size) -> bool
{
  return *buf == size;
}
