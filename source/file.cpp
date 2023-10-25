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
    auto val = std::make_unique<char>();
    m_file->read(val.get(), sizeof(char));

    return *val;
  }

  m_ok = false;
  return 0;
}

auto b3dm::file_stream::read_string(size_t size, std::string& out_string) -> bool
{
  if (m_file->good()) {
    auto buffer = std::make_unique<char[]>(size + 1);
    m_file->read(buffer.get(), size);

    out_string = buffer.get();
  }

  m_ok = m_file->good();
  return m_ok;
}

auto b3dm::file_stream::read(uint8_t* buf, uint32_t size) -> bool
{
  if (m_file->good()) {
    m_file->read(reinterpret_cast<char*>(buf), size);
  }

  m_ok = m_file->good();
  return m_ok && m_file->gcount() == size;
}

auto b3dm::file_stream::seek(size_t abs_pos) -> void
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
    return ((byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1);
  }

  return 0;
}
auto b3dm::file_stream::write8(uint8_t value) -> void {}

auto b3dm::file_stream::write(const uint8_t* buf, uint32_t size) -> bool
{
  return *buf == size;
}
