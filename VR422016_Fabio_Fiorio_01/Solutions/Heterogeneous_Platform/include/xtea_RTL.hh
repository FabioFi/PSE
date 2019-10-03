#ifndef xtea_RTL_H
#define xtea_RTL_H

//Mi arriva il valore threshold dal controllore TLM cifrato, lo devo decifrare e devo decidere se aprire, chiudere o lasciare com'è.

#include "systemc.h"
// #include <systemc-ams> //da togliere

SC_MODULE(xtea_RTL){

  //typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3} STATES;
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
  // sca_tdf::sca_out<sc_uint<32> > result0;
  // sca_tdf::sca_out<sc_uint<32> > result1;
  sc_out<sc_uint<1> > output_rdy;

  sc_in<bool> rst;
  sc_in<bool> clk;

  //SC_HAS_PROCESS(xtea_RTL);

  /*xtea_RTL(sc_core::sc_module_name module_name );
  ~xtea_RTL();*/

  typedef enum {Reset_ST, ST_0, ST_1, ST_2, ST_3, ST_4, ST_5, ST_6, ST_7, ST_8, ST_9, ST_10, Final_ST, Wait_RESULT} STATES;

  /*sc_signal<STATES> STATUS, NEXT_STATUS;
  sc_signal<sc_uint<32> > Product;
  sc_signal<sc_uint<32> > NumberA;
  sc_signal<sc_uint<32> > NumberB;
  sc_signal<sc_uint<5> >  Counter;

  void elaborate_MULTIPLICATION(void);      // xtea_RTL.cc
  void elaborate_MULTIPLICATION_FSM(void);*/  // xtea_RTL.cc

  sc_signal<STATES> STATUS, NEXT_STATUS;
  sc_signal<sc_uint<6> > counter;
  sc_signal<sc_uint<32> > delta;
  sc_signal<sc_uint<32> > v0;
  sc_signal<sc_uint<32> > v1;
  sc_signal<sc_uint<64> > sum;
  sc_signal<sc_uint<32> > temp0;
  sc_signal<sc_uint<32> > temp1;

  void fsm(void);
  void datapath(void);

// Costruttore di SC_MODULE(xtea_RTL)
  SC_CTOR(xtea_RTL){
    SC_METHOD(datapath);
    sensitive << rst.neg();
    sensitive << clk.pos();

    SC_METHOD(fsm);
    //sensitive << STATUS << number_isready << number_portAI << number_portAF << number_portBI << number_portBF << Counter;
    sensitive << STATUS << input_rdy << word1 << word2 << counter;
  };
};

#endif
