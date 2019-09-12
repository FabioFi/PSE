#ifndef __define_LT_h__
#define __define_LT_h__

#include <systemc.h>
//#include "sc_fixed.h"

struct iostructV {
  int flag;
  double threshold;
};

struct iostructT {
  double livello_acqua;
};

/*struct iostructR{
  sc_dt::sc_fixed<16,8> n1;
  sc_dt::sc_fixed<16,8> n2;
  sc_dt::sc_fixed<32,16> result;
};*/

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
};

#define ADDRESS_TYPE int
#define DATA_TYPE1 iostructV
#define DATA_TYPE2 iostructT
#define DATA_TYPE3 iostructR

#define DATA_TYPE iostruct

#endif
