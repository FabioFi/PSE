#ifndef __define_LT_h__
#define __define_LT_h__

#include <systemc.h>

struct iostruct {

  sc_uint<32> datain_word1;
  sc_uint<32> datain_word2;
  sc_uint<32> datain_key0;
  sc_uint<32> datain_key1;
  sc_uint<32> datain_key2;
  sc_uint<32> datain_key3;


  sc_uint<32> result0;
  sc_uint<32> result1;

  sc_logic mode;

  //sc_int<32> datain;
  //sc_int<32> result;
  
};

#define ADDRESS_TYPE int
#define DATA_TYPE iostruct

#endif
