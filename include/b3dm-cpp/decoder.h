//
// Created by Daniil on 9/25/2023.
//

#ifndef B3DM_CPP_SOURCE_DECODER_H_
#define B3DM_CPP_SOURCE_DECODER_H_

#include <cstdint>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

#include "stream_interface.h"

namespace b3dm
{

struct file_header
{
};

struct file_body
{
};

class B3DM_CPP_EXPORT decoder
{
public:
  decoder(file_interface* file_interface, void* decoder_delegate);

  auto get_header() -> const file_header& { return m_header; }
  auto get_body() -> const file_body& { return m_body; }

  auto read_header() -> bool { return false; }
  auto read_body() -> bool { return false; }

private:
  file_interface* m_file;
  file_header m_header;
  file_body m_body;
};

}  // namespace b3dm

#endif  // B3DM_CPP_SOURCE_DECODER_H_
