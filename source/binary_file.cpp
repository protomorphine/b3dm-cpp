//
// Created by D.Zaycev on 26.09.2023.
//

#include <memory>

#include "b3dm-cpp/binary_file.h"

b3dm::streams::binary_file::binary_file(const std::filesystem::path& file_name)
    : m_file(std::make_unique<std::ifstream>(file_name, std::ios::binary)) { }

auto b3dm::streams::binary_file::read8() -> uint8_t {
  if(m_file->good()) {
    auto val = std::make_unique<char>();
    m_file->read(val.get(), sizeof(char));

    return static_cast<uint8_t>(*val);
  }

  m_ok = false;
  return 0;
}

auto b3dm::streams::binary_file::read(char* buf, size_t size) -> bool {
  if(m_file->good()) {
    m_file->read(buf, static_cast<std::streamoff>(size));
  }

  m_ok = m_file->good();
  return m_ok && m_file->gcount() == static_cast<std::streamsize>(size);
}

auto b3dm::streams::binary_file::read32() -> uint32_t {
  auto byte1 = static_cast<std::byte>(read8());
  auto byte2 = static_cast<std::byte>(read8());
  auto byte3 = static_cast<std::byte>(read8());
  auto byte4 = static_cast<std::byte>(read8());

  if(ok()) {
    return bytes_to_uint(byte4, byte3, byte2, byte1);
  }

  return 0;
}
