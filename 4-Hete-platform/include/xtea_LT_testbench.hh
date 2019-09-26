#ifndef _xtea_LT_TESTBENCH_H_
#define _xtea_LT_TESTBENCH_H_

//Mi arriva il valore threshold dal water tank (ams) -> lo devo cifrare e mandare all'RTL. NO -> devo mandare se aprire o chiudere o nulla

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "define_LT.hh"

class xtea_LT_testbench
  : public sc_module
  , public virtual tlm::tlm_bw_transport_if<>
{

private:

  SC_HAS_PROCESS(xtea_LT_testbench);

  virtual void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range);

  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t);

  //virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);

  void xtea_function();

  tlm_utils::tlm_quantumkeeper m_qk;

  void run();
  void clock_gen();

public:

  tlm::tlm_initiator_socket<> initiator_socket_serbatoio;
//  tlm::tlm_initiator_socket<> initiator_socket_valvola;
//  tlm::tlm_initiator_socket<> initiator_socket_rtl;

  // TLM socket
  tlm::tlm_initiator_socket<> initiator_socket;

  double livello_acqua_in;
  double threshold;
  sc_core::sc_signal<int> flag;
  iostruct xtea_packet;


  // constructor
  xtea_LT_testbench(sc_module_name name);

};

#endif
