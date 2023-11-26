//
// Created by D.Zaycev on 26.09.2023.
//

#include <memory>

#include "b3dm-cpp/file.h"

b3dm::streams::binary_file::binary_file(const std::filesystem::path& file_name)
    : m_file(std::make_unique<std::ifstream>(file_name, std::ios::binary))
{
}

auto b3dm::streams::binary_file::read8() -> uint8_t
{
  if (m_file->good()) {
    auto val = std::make_unique<char>();
    m_file->read(val.get(), sizeof(char));

    return *val;
  }

  m_ok = false;
  return 0;
}

auto b3dm::streams::binary_file::read(char* buf, size_t size) -> bool
{
  if (m_file->good()) {
    m_file->read(buf, static_cast<std::streamoff>(size));
  }

  m_ok = m_file->good();
  return m_ok && m_file->gcount() == size;
}

auto b3dm::streams::binary_file::read32() -> int
{
  uint8_t constexpr byte2_shift = 8;
  uint8_t constexpr byte3_shift = 16;
  uint8_t constexpr byte4_shift = 24;

  uint8_t const byte1 = read8();
  uint8_t const byte2 = read8();
  uint8_t const byte3 = read8();
  uint8_t const byte4 = read8();

  if (ok()) {
    return ((byte4 << byte4_shift) | (byte3 << byte3_shift) | (byte2 << byte2_shift) | byte1);  // NOLINT(*-signed-bitwise)
  }

  return 0;
}
