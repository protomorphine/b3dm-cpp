//
// Created by D.Zaycev on 26.09.2023.
//

#include <memory>
#include <vector>

#include "b3dm-cpp/file.h"

b3dm::file_stream::file_stream(std::unique_ptr<std::ifstream> stream)
    : m_file(std::move(stream))
{
}

b3dm::file_stream::file_stream(std::string_view file_name)
    : m_file(std::make_unique<std::ifstream>(file_name.data(), std::ios::binary))
{
}

auto b3dm::file_stream::read8() -> uint8_t
{
  if(m_file->good()) {
    auto val = std::make_unique<char>();
    m_file->read(val.get(), sizeof(char));

    return *val;
  }

  m_ok = false;
  return 0;
}

auto b3dm::file_stream::read_string(size_t size, std::string& out_string) -> bool
{
  if(m_file->good()) {
    auto buffer = std::make_unique<char_buffer>(size + 1);
    read(buffer.get()->data(), size);

    out_string = buffer.get()->data();
  }

  m_ok = m_file->good();
  return m_ok;
}

auto b3dm::file_stream::read(char* buf, size_t size) -> bool
{
  if(m_file->good()) {
    m_file->read(buf, static_cast<std::streamoff>(size));
  }

  m_ok = m_file->good();
  return m_ok && m_file->gcount() == size;
}

auto b3dm::file_stream::read32() -> int
{
  uint8_t constexpr byte2_shift {8U};
  uint8_t constexpr byte3_shift {16U};
  uint8_t constexpr byte4_shift {24U};

  uint8_t const byte1 = read8();
  uint8_t const byte2 = read8();
  uint8_t const byte3 = read8();
  uint8_t const byte4 = read8();

  if(ok()) {
    return ((byte4 << byte4_shift) | (byte3 << byte3_shift) | (byte2 << byte2_shift) | byte1);
  }

  return 0;
}

auto b3dm::file_stream::read(size_t size) -> std::unique_ptr<char_buffer>
{
  auto buffer = std::make_unique<char_buffer>(size);
  read(buffer.get()->data(), size);
  return buffer;
}
