#ifndef xtea_RTL_H
#define xtea_RTL_H

#include "systemc.h"

SC_MODULE(xtea_RTL){

  /*sc_in<sc_uint<1> >       din_rdy;
  sc_in<sc_uint<32> >      din;
  sc_out<sc_uint<32> >     dout;
  sc_out<sc_uint<1> >      dout_rdy;
  sc_in<bool>              rst;*/
  //sc_in< sc_dt::sc_logic > clk;

  sc_in<sc_uint<1> > input_rdy;
  sc_in<sc_uint<32> > word1;
  sc_in<sc_uint<32> > word2;
  sc_in<sc_uint<32> > key0;
  sc_in<sc_uint<32> > key1;
  sc_in<sc_uint<32> > key2;
  sc_in<sc_uint<32> > key3;
  sc_in<sc_uint<1> > mode;

  sc_out<sc_uint<32> > result0;
  sc_out<sc_uint<32> > result1;
  sc_out<sc_uint<1> > output_rdy;

  sc_in<bool> rst;
  sc_in<bool> clk;

  typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4, ST_5, ST_6, ST_7, ST_8, ST_9, ST_10, Final_ST} STATES;

  sc_signal<STATES> STATUS, NEXT_STATUS;
  /*sc_signal<sc_uint<32> > Rem;
  sc_signal<sc_uint<32> > xtea;
  sc_signal<sc_uint<32> > Number;
  sc_signal<sc_uint<5> >  Counter;*/
  sc_signal<sc_uint<6> > counter;
  sc_signal<sc_uint<32> > delta;
  sc_signal<sc_uint<32> > v0;
  sc_signal<sc_uint<32> > v1;
  sc_signal<sc_uint<64> > sum;
  sc_signal<sc_uint<32> > temp0;
  sc_signal<sc_uint<32> > temp1;

  void fsm(void);
  void datapath(void);

  SC_CTOR(xtea_RTL){
    SC_METHOD(datapath);
    sensitive << rst.neg();
    sensitive << clk.pos();


    SC_METHOD(fsm);
    //sensitive << STATUS << din_rdy << din << Counter;
    sensitive << STATUS << input_rdy << word1 << word1 << counter;
  };
};

#endif
