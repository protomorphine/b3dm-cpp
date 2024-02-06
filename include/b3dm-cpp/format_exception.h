//
// Created by kuper on 26.11.2023.
//

#pragma once

#include <exception>
#include <string>
namespace b3dm::exceptions
{

/// @brief incorrect format exception. Raises when passed header magic string is not 'b3dm'
class IncorrectFormat : public std::exception
{
public:
  IncorrectFormat() = default;

  /// @brief Returns a C-style character string describing the general cause of the current error.
  /// @return C-style character string describing the general cause of the current error.
  auto what() const noexcept -> const char* override { return "incorrect b3dm format!"; }
};

}  // namespace b3dm::exceptions
