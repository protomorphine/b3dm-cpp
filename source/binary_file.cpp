//
// Created by D.Zaycev on 26.09.2023.
//

#include "b3dm-cpp/binary_file.h"

#include <memory>

b3dm::streams::BinaryFile::BinaryFile(std::istream& stream) : m_file_(stream) {}

auto b3dm::streams::BinaryFile::Read8() -> uint8_t {
  if (m_file_.good()) {
    auto val = std::make_unique<char>();
    m_file_.read(val.get(), sizeof(char));

    return static_cast<uint8_t >(*val);
  }

  m_ok_ = false;
  return 0;
}

auto b3dm::streams::BinaryFile::Read(char* buf, size_t size) -> bool {
  if (m_file_.good()) {
    m_file_.read(buf, static_cast<std::streamoff>(size));
  }

  m_ok_ = m_file_.good();
  return m_ok_ && m_file_.gcount() == static_cast<std::streamsize>(size);
}

auto b3dm::streams::BinaryFile::Read32() -> uint32_t {
  auto byte1 = static_cast<std::byte>(Read8());
  auto byte2 = static_cast<std::byte>(Read8());
  auto byte3 = static_cast<std::byte>(Read8());
  auto byte4 = static_cast<std::byte>(Read8());

  if (Ok()) {
    return BytesToUint(byte4, byte3, byte2, byte1);
  }

  return 0;
}
