//
// Created by D.Zaycev on 26.09.2023.
//

#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>

#include "b3dm-cpp/binary_readonly_stream.h"

namespace b3dm::streams
{

/// @brief wrapper for ifstream
/// @see ifstream
class B3DM_CPP_EXPORT binary_file : public binary_readonly_stream
{
public:
  explicit binary_file(const std::filesystem::path& file_name);

  /// @brief is file_stream in ok state.
  /// @return true - if file_stream in ok state, otherwise - false.
  auto ok() const -> bool override { return m_ok; }

  /// @brief reads 1 byte from stream.
  /// @return byte.
  auto read8() -> uint8_t override;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if read succeed, otherwise - false.
  auto read(char* buf, size_t size) -> bool override;

  /// @brief read 4 bytes, and concatenate them in int32.
  /// @return int32.
  auto read32() -> uint32_t override;

private:
  /// @brief converts std::byte's to unsigned integral type
  /// @param bytes sequence of std::byte
  /// @return unsigned integral value from bytes
  constexpr auto bytes_to_uint(std::same_as<std::byte> auto... bytes) -> std::unsigned_integral auto
  {
    constexpr auto byte_length = sizeof...(bytes);

    static_assert(byte_length <= sizeof(uint64_t));

    using result_type = std::conditional_t<
        (byte_length == 1),
        std::uint8_t,
        std::conditional_t<
            (byte_length == 2),
            std::uint16_t,
            std::conditional_t<(byte_length == 4), std::uint32_t, std::uint64_t>>>;

    return [&]<std::size_t... S>(std::index_sequence<S...>)
    {
      // Accumulate the part of the number using the bitwise or operator for each byte
      return ((static_cast<result_type>(bytes) << CHAR_BIT * (byte_length - S - 1)) | ...);
    }(std::make_index_sequence<byte_length> {});
  }

  std::unique_ptr<std::ifstream> m_file;
  bool m_ok = true;
};

}  // namespace b3dm::streams
