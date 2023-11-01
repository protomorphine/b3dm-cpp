//
// Created by D.Zaycev on 26.09.2023.
//

#include <memory>

#include "b3dm-cpp/file.h"

b3dm::file_stream::file_stream(std::unique_ptr<std::ifstream> stream)
    : m_file(std::move(stream))
    , m_ok(true)
{
}

b3dm::file_stream::file_stream(std::string_view file_name)
    : m_file(
        std::make_unique<std::ifstream>(file_name.data(), std::ios::binary))
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

auto b3dm::file_stream::read_string(size_t size, std::string& out_string)
    -> bool
{
  if (m_file->good()) {
    auto buffer = std::make_unique<char[]>(size + 1);
    m_file->read(buffer.get(), size);

    out_string = buffer.get();
  }

  m_ok = m_file->good();
  return m_ok;
}

auto b3dm::file_stream::read(char* buf, size_t size) -> bool
{
  if (m_file->good()) {
    m_file->read(buf, size);
  }

  m_ok = m_file->good();
  return m_ok && m_file->gcount() == size;
}

auto b3dm::file_stream::read32() -> int
{
  unsigned char const byte1 = read8();
  unsigned char const byte2 = read8();
  unsigned char const byte3 = read8();
  unsigned char const byte4 = read8();

  if (ok()) {
    return ((byte4 << 24U) | (byte3 << 16U) | (byte2 << 8U) | byte1);
  }

  return 0;
}

auto b3dm::file_stream::read(size_t size) -> std::unique_ptr<char[]>
{
  auto buffer = std::make_unique<char[]>(size);
  read(buffer.get(), size);
  return buffer;
}
