#include <systemc.h>
#include <tlm.h>
#include "xtea_LT_testbench.hh"
#include "xtea_RTL_transactor.hh"
#include "xtea_RTL.hh"

#define PERIOD 10

SC_MODULE(main_RTL)
{

  // CLOCK SIGNAL
  //sc_signal< sc_dt::sc_logic > clk;
  sc_signal<bool> clk;

  void clk_gen()
  {
    while( true )
    {
      clk.write( true ); //sc_dt::SC_LOGIC_1
      wait( PERIOD / 2, sc_core::SC_NS );
      clk.write( false ); //sc_dt::SC_LOGIC_0
      wait( PERIOD / 2, sc_core::SC_NS );
    }
  }

  // RESET SIGNAL
  //sc_signal<bool> clock;
  sc_signal < bool >        rst;

  // OTHER SIGNALS
  /*sc_signal<sc_uint<1> >  	dout_rdy;
  sc_signal<sc_uint<32> > 	dout;
  sc_signal<sc_uint<1> >  	din_rdy;
  sc_signal<sc_uint<32> > 	din;*/
  sc_signal<sc_uint<1> > input_rdy;
  sc_signal<sc_uint<32> > word1;
  sc_signal<sc_uint<32> > word2;
  sc_signal<sc_uint<32> > key0;
  sc_signal<sc_uint<32> > key1;
  sc_signal<sc_uint<32> > key2;
  sc_signal<sc_uint<32> > key3;
  sc_signal<sc_uint<1> > mode;
  sc_signal<sc_uint<32> > result0;
  sc_signal<sc_uint<32> > result1;
  sc_signal<sc_uint<1> > output_rdy;

  //Definition
  xtea_LT_testbench		  tb;	       // source module
  xtea_RTL_transactor		transactor; // xtea transactor
  xtea_RTL			        xtea;    // xtea RTL module

  //Construct
  SC_CTOR(main_RTL)
    : tb("tb")
    , transactor("transactor")
    , xtea("xtea")
  {

    SC_THREAD( clk_gen );

    // TLM testbench <-> Transactor binding (TLM interface)
    tb.initiator_socket(transactor.target_socket);

    // RTL design <-> Transactor binding (RTL interfaces)
    /*xtea.clk(clk);
    xtea.rst(rst);
    xtea.din_rdy(din_rdy);
    xtea.din(din);
    xtea.dout(dout);
    xtea.dout_rdy(dout_rdy);*/
    xtea.input_rdy(input_rdy);
    xtea.word1(word1);
    xtea.word2(word2);
    xtea.key0(key0);
    xtea.key1(key1);
    xtea.key2(key2);
    xtea.key3(key3);
    xtea.mode(mode);
    xtea.result0(result0);
    xtea.result1(result1);
    xtea.output_rdy(output_rdy);
    xtea.clk(clk); //(clock)
    xtea.rst(rst);

    /*transactor.clk(clk);
    transactor.rst(rst);
    transactor.din_rdy(din_rdy);
    transactor.din(din);
    transactor.dout(dout);
    transactor.dout_rdy(dout_rdy);*/
    transactor.input_rdy(input_rdy);
    transactor.word1(word1);
    transactor.word2(word2);
    transactor.key0(key0);
    transactor.key1(key1);
    transactor.key2(key2);
    transactor.key3(key3);
    transactor.mode(mode);
    transactor.result0(result0);
    transactor.result1(result1);
    transactor.output_rdy(output_rdy);
    transactor.clk(clk); //(clock)
    transactor.rst(rst);

  }

};

int sc_main(int argc, char **argv)
{
  sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
  main_RTL* topl;

  topl = new main_RTL("topl");

  sc_start();

  return(0);

};
