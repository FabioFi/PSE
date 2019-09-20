#include "xtea_LT_testbench.hh"
#include <sstream>
#include <iostream>
#include <iomanip>

//Mi arriva il valore threshold dal water tank (ams) -> lo devo cifrare e mandare all'RTL. NO -> devo mandare se aprire o chiudere o nulla

void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{

}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - nb_transport_bw"<<endl;
  return tlm::TLM_COMPLETED;
}


//-------------------------------------------convertitore-----------------------
std::string double2hexstr(double x) {
    union
    {
        uint64_t i;
        double    d;
    } value;

   value.d = x;

   std::ostringstream buf;
   buf << std::hex << std::setfill('0') << std::setw(8) << value.i;

   return buf.str().substr(0, 8);
}
//------------------------------------------------------------------------------

void xtea_LT_testbench::run()
{

  sc_time local_time = m_qk.get_local_time();

  //iostructR binary_packet;
  iostructV valvola_packet;
  iostructT serbatoio_packet;
  // First transaction (initialization)
  iostruct xtea_packet;

  cout<<sc_simulation_time()<<" - "<<name()<<" - run (xtea_LT_testbench)"<<endl;

  tlm::tlm_generic_payload payload_binary;
  tlm::tlm_generic_payload payload_valvola;
  tlm::tlm_generic_payload payload_serbatoio;

  tlm::tlm_generic_payload payload;

  //xtea_packet.datain_word1 = 0x12345678; //da sostituire con il segnale di apertura o chiusura
  //xtea_packet.datain_word2 = 0x9abcdeff; //da sostituire con il valore della threshold
  xtea_packet.datain_key0 = 0x6a1d78c8;
  xtea_packet.datain_key1 = 0x8c86d67f;
  xtea_packet.datain_key2 = 0x2a65bfbe;
  xtea_packet.datain_key3 = 0xb4bd6e46;

  xtea_packet.result0 = 0;
  xtea_packet.result1 = 0;
  xtea_packet.mode = 1; //true (decryption)

  livello_acqua_in=0;
  threshold=0.7;

  /* while(true){
  *
  *
  */


  //-----------------------CALCOLO THRESHOLD-------------------------------------------
  valvola_packet.flag = flag;
  valvola_packet.threshold = threshold;
  payload_valvola.set_data_ptr((unsigned char*) &valvola_packet);
  payload_valvola.set_write();

  initiator_socket_valvola->b_transport(payload_valvola, local_time);

  if(payload_valvola.get_response_status() == tlm::TLM_OK_RESPONSE){
  }

  wait(100, SC_MS);

  payload_serbatoio.set_data_ptr((unsigned char*) &serbatoio_packet);
  payload_serbatoio.set_read();
  initiator_socket_serbatoio->b_transport(payload_serbatoio, local_time);
  if(payload_serbatoio.get_response_status() == tlm::TLM_OK_RESPONSE){
    livello_acqua_in=serbatoio_packet.livello_acqua;
  }


  if(livello_acqua_in < 5){
    xtea_packet.n2 = 1.1;
    flag = 1;
  } else if (livello_acqua_in > 8.8){
    xtea_packet.n2 = 0.7;
    flag = 2;
  } else if (livello_acqua_in > 5 && livello_acqua_in < 8.8){
    flag = 0;
    xtea_packet.n2=1;
  }
  xtea_packet.n1 = threshold;

  payload_binary.set_data_ptr((unsigned char*) &xtea_packet);
  payload_binary.set_write();
  initiator_socket_rtl->b_transport(payload_binary, local_time);
  payload_binary.set_read();
  initiator_socket_rtl->b_transport(payload_binary, local_time);
  if(payload_binary.get_response_status() == tlm::TLM_OK_RESPONSE){
    threshold=xtea_packet.result;
  }

  m_qk.set(local_time);
  if (m_qk.need_sync()) {
    m_qk.sync();
  }

  //----------------------------convertire i dati in hex------------------------
  /*double b = xtea_packet.n2;
  union {
      double fval ;
      uint64_t ival ;
  };
  fval = b ;
  std::ostringstream stm ;
  stm << std::hex << std::uppercase << ival ;
  cout << b << " to hex = 0x" << stm.str() <<" ->(open/close/idle) this is right !!!!" <<endl;

  double c = xtea_packet.n1; // = threshold;
  union {
      double fval1 ;
      uint64_t ival1 ;
  };
  fval1 = c ;
  std::ostringstream stm1 ;
  stm1 << std::hex << std::uppercase << ival1 ;
  cout << c << " to hex = 0x" << stm1.str() <<" ->(threshold) this is right !!!!" <<endl;*/



  cout << "0x-" << double2hexstr(xtea_packet.n2) << " - AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
  cout << "0x-" << double2hexstr(xtea_packet.n1) << " - BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB" << endl;

  cout << "Open/Close/Idle: " << xtea_packet.n2 << endl;
  cout << "Threshold: " << xtea_packet.n1 << endl;

  xtea_packet.datain_word1 = /*stm;*/ /*double2hexstr(*/xtea_packet.n2/*)*/; //apertura o chiusura (1.1 0.7 1)
  xtea_packet.datain_word2 = /*stm1;*/ /*double2hexstr(*/xtea_packet.n1/*)*/; //threshold

  //-----------------------ECRYPTION-------------------------------------------

  cout << "First invocation: \n";
  cout << " - the encryption of " << std::hex << xtea_packet.datain_word1 << " and " << std::hex << xtea_packet.datain_word2 << endl;
  cout << " - with key " << std::hex << xtea_packet.datain_key0 << xtea_packet.datain_key1 << xtea_packet.datain_key2 << xtea_packet.datain_key3 << "\n";

  payload.set_data_ptr((unsigned char*) &xtea_packet); // set payload data
  payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator
  payload.set_write(); // write transaction

  // update the local time variable to send it to the target
  local_time = m_qk.get_local_time();

  // start write transaction
  cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
  initiator_socket->b_transport(payload, local_time);

  // start read transaction
  payload.set_read();
  initiator_socket->b_transport(payload, local_time);

  if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    cout<<"[TB:] Result is: " << std::hex << xtea_packet.result0 << " and " << std::hex << xtea_packet.result1 << endl;
  }

  // temporal decoupling> get time and check if we have to synchronize with the target
  cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
  m_qk.set(local_time);
  if (m_qk.need_sync()) {
    // synchronize simulation time
    cout << "SYNCHRONIZING" << endl;
    m_qk.sync();
    cout << "#####################" << endl;
  }

  printf("Done!!\n");

  // --- dati threshold ---

  /*while(true){
    valvola_packet.flag = flag;
    valvola_packet.threshold = threshold;
    payload_valvola.set_data_ptr((unsigned char*) &valvola_packet);
    payload_valvola.set_write();

    initiator_socket_valvola->b_transport(payload_valvola, local_time);

    if(payload_valvola.get_response_status() == tlm::TLM_OK_RESPONSE){
    }

    wait(100, SC_MS);

    payload_serbatoio.set_data_ptr((unsigned char*) &serbatoio_packet);
    payload_serbatoio.set_read();
    initiator_socket_serbatoio->b_transport(payload_serbatoio, local_time);
    if(payload_serbatoio.get_response_status() == tlm::TLM_OK_RESPONSE){
      livello_acqua_in=serbatoio_packet.livello_acqua;
    }


    if(livello_acqua_in < 5){
      xtea_packet.n2 = 1.1;
      flag = 1;
    } else if (livello_acqua_in > 8.8){
      xtea_packet.n2 = 0.7;
      flag = 2;
    } else if (livello_acqua_in > 5 && livello_acqua_in < 8.8){
      flag = 0;
      xtea_packet.n2=1;
    }
    xtea_packet.n1 = threshold;

    payload_binary.set_data_ptr((unsigned char*) &xtea_packet);
    payload_binary.set_write();
    initiator_socket_rtl->b_transport(payload_binary, local_time);
    payload_binary.set_read();
    initiator_socket_rtl->b_transport(payload_binary, local_time);
    if(payload_binary.get_response_status() == tlm::TLM_OK_RESPONSE){
      threshold=xtea_packet.result;
    }

    m_qk.set(local_time);
    if (m_qk.need_sync()) {
      m_qk.sync();
    }
  }*/

  sc_stop();

}

// constructor
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  initiator_socket_valvola(*this);
  initiator_socket_serbatoio(*this);
  initiator_socket_rtl(*this);

  // initialize TLM socket
  initiator_socket(*this);

  // run is a thread
  SC_THREAD(run);

  // set parameters for temporal decoupling
  // one quantum is made of 500 ns
  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}
