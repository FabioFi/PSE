#ifndef __xtea_RTL_transactor_HPP__
#define __xtea_RTL_transactor_HPP__

#include <systemc.h>
#include <tlm.h>
#include "define_LT.hh"

class xtea_RTL_transactor
  : public sc_module
  , public virtual tlm::tlm_fw_transport_if<>
  {
  public:

    //Lato TLM
    tlm::tlm_target_socket<> target_socket;
    //iostructR ioDataStruct;
    iostruct  ioDataStruct;
    tlm::tlm_generic_payload* pending_transaction;
    sc_time timing_annotation;
    sc_event begin_write, end_write, begin_read, end_read;


    //interfaccia TLM
    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& t);
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);


    //Porte
    /*sc_in<bool > p_In_enable;
    sc_out<sc_uint<8> > number_portAI;
    sc_out<sc_uint<8> > number_portAF;
    sc_out<sc_uint<8> > number_portBI;
    sc_out<sc_uint<8> > number_portBF;
    sc_in<sc_uint<8> > result_portAI;
    sc_in<sc_uint<8> > result_portAF;
    sc_in<sc_uint<8> > result_portBI;
    sc_in<sc_uint<8> > result_portBF;
    sc_out<bool > p_Out_enable;
    sc_out<bool > reset_to_RTL;
    sc_in< sc_logic > clk;
    sc_signal<bool > rst;*/

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

    //Processi
    void WRITEPROCESS();
    void READPROCESS();

    void sync();
    void end_of_elaboration();
    void reset();

    SC_HAS_PROCESS(xtea_RTL_transactor);
    xtea_RTL_transactor(sc_module_name name_);

  private:
    sc_uint<8> AI,AF,BI,BF;
    sc_dt::sc_fixed<32,16> risultato;
    sc_uint<32> res_uint;
  };

  #endif
