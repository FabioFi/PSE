/// @file   hif_verilog_standard.cc
/// @author Enrico Fraccaroli
/// @date   Sep 05 2017

#include "hif_verilog_standard.hh"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace hif_verilog_standard
{

bool hif_verilog__system_readmemh(const std::string & fileName,
                                  uint8_t * memory,
                                  const size_t & start_x,
                                  const size_t & end_x,
                                  const size_t & start_y,
                                  const size_t & end_y)
{
    std::ifstream infile(fileName.c_str(), std::ifstream::in);
    if (!infile.is_open())
    {
        return false;
    }
    int i =0;
    int a =0;
    
    while(!infile.eof()) {

      infile >> std::hex >> a;
      //std::cout << "variable: " <<std::hex<< std::setw(2) << std::setfill('0') <<  a << std::endl;
      memory[i] = a;
      //std::cout << "Memory: "<< std::hex<< std::setw(2) << std::setfill('0') <<  unsigned(memory[i]) << std::endl;
      i++;

    }
    //getchar();

    infile.close();
    return true;
}

}
