//
// Created by Daniil on 9/25/2023.
//

#ifndef B3DM_CPP_SOURCE_DECODER_H_
#define B3DM_CPP_SOURCE_DECODER_H_

#include <cstdint>
#include <fstream>

#include <b3dm-cpp/b3dm-cpp_export.hpp>

#include "file.h"
#include "stream_interface.h"

namespace b3dm
{

constexpr std::string_view b3dm_magic = "b3dm";
constexpr size_t b3dm_header_length = 28;

struct header
{
  std::string magic;
  uint32_t version;
  uint32_t byte_length;
  uint32_t feature_table_json_byte_length;
  uint32_t feature_table_binary_byte_length;
  uint32_t batch_table_json_byte_length;
  uint32_t batch_table_binary_byte_length;
};

struct body
{
  std::string feature_table_json;
  uint8_t* feature_table;

  std::string batch_table_json;
  uint8_t* batch_table;

  uint8_t* gltf_data;
};

class B3DM_CPP_EXPORT decoder
{
public:
  explicit decoder(file_stream* file_interface);

  auto get_header() -> const header& { return m_header; }

  auto get_body() -> const body& { return m_body; }

  auto read_header() -> bool;

  auto read_body() -> bool;

private:
  file_stream* m_file;
  header m_header;
  body m_body;
};

}  // namespace b3dm

#endif  // B3DM_CPP_SOURCE_DECODER_H_
