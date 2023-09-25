//
// Created by Daniil on 9/25/2023.
//

#include <iostream>

#include "b3dm-cpp/decoder.h"
b3dm::decoder::decoder(b3dm::file_interface* file_interface, void* decoder_delegate) : m_file(file_interface)
{
  std::cout << "b3dm::decoder::decoder called" << std::endl;
}
