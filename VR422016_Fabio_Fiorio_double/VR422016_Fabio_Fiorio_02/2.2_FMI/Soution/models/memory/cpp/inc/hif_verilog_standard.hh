/// @file   hif_verilog_standard.hh
/// @author Enrico Fraccaroli
/// @date   Sep 05 2017

#pragma once

#include <string>

namespace hif_verilog_standard
{

bool hif_verilog__system_readmemh(const std::string & fileName,
                                  uint8_t * memory,
                                  const size_t & start_x,
                                  const size_t & end_x,
                                  const size_t & start_y,
                                  const size_t & end_y);
}
