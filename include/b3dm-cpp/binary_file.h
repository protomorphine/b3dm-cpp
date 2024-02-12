//
// Created by D.Zaycev on 26.09.2023.
//

#pragma once

#include <climits>
#include <concepts>
#include <filesystem>
#include <fstream>

#include "b3dm-cpp/stream.h"

namespace b3dm::streams {

/// @brief wrapper for ifstream
/// @see ifstream
class B3DM_CPP_EXPORT [[maybe_unused]] BinaryFile final : public IStream {
 public:
  [[maybe_unused]] explicit BinaryFile(std::istream& stream);

  /// @brief is file_stream in Ok state.
  /// @return true - if file_stream in Ok state, otherwise - false.
  auto Ok() const -> bool override { return m_ok_; }

  /// @brief reads 1 byte from stream.
  /// @return byte.
  auto Read8() -> uint8_t override;

  /// @brief reads binary data.
  /// @param[out] buf buffer with data.
  /// @param[in] size length of data.
  /// @return true - if Read succeed, otherwise - false.
  auto Read(char* buf, size_t size) -> bool override;

  /// @brief Read 4 bytes, and concatenate them in int32.
  /// @return int32.
  auto Read32() -> uint32_t override;

 private:
  /// @brief converts std::byte's to unsigned integral type
  /// @param bytes sequence of std::byte
  /// @return unsigned integral value from bytes
  constexpr auto BytesToUint([[maybe_unused]] std::same_as<std::byte> auto... bytes) -> std::unsigned_integral auto {
    constexpr auto kByteLength = sizeof...(bytes);

    static_assert(kByteLength <= sizeof(uint64_t));

    using result_type =
        std::conditional_t<(kByteLength == 1), std::uint8_t,
                           std::conditional_t<(kByteLength == 2), std::uint16_t,
                                              std::conditional_t<(kByteLength == 4), std::uint32_t, std::uint64_t>>>;

    return [&]<std::size_t... S>(std::index_sequence<S...>) {
      // Accumulate the part of the number using the bitwise or operator for each byte
      return ((static_cast<result_type>(bytes) << CHAR_BIT * (kByteLength - S - 1)) | ...);
    }(std::make_index_sequence<kByteLength>{});
  }

  std::istream& m_file_;
  bool m_ok_ = true;
};

}  // namespace b3dm::streams
