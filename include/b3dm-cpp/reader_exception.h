//
// Created by kuper on 26.11.2023.
//

#pragma once

#include <exception>
#include <string>
namespace b3dm::exceptions
{

/// @brief reader exception. Raises when couldn't Read data from file.
class ReaderException : public std::exception
{
public:
  ReaderException() = default;

  /// @brief Returns a C-style character string describing the general cause of the current error.
  /// @return C-style character string describing the general cause of the current error.
  auto what() const noexcept -> const char* override { return "unable to Read data"; }
};

}  // namespace b3dm::exceptions
