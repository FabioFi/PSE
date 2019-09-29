#include "xtea_LT_testbench.hh"
// #include <sstream>
// #include <iostream>
// #include <iomanip>

//Mi arriva il valore threshold dal water tank (ams) -> lo devo cifrare e mandare all'RTL. NO -> devo mandare se aprire o chiudere o nulla

void xtea_LT_testbench::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range)
{

}

tlm::tlm_sync_enum xtea_LT_testbench::nb_transport_bw(tlm::tlm_generic_payload &  trans, tlm::tlm_phase &  phase, sc_time &  t)
{
  cout<<sc_simulation_time()<<" - "<<name()<<" - nb_transport_bw"<<endl;
  return tlm::TLM_COMPLETED;
}

/*void xtea_LT_testbench::b_transport(tlm::tlm_generic_payload& trans, sc_time& t)
{
  //timing_annotation = SC_ZERO_TIME;
  wait(0, SC_NS);

  xtea_packet = *((iostruct*) trans.get_data_ptr());

  if (trans.is_write()) {
    cout<<"\t\t[xtea:] Received invocation of the b_transport primitive - write"<<endl;
    //*((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    xtea_packet=*((iostruct*) trans.get_data_ptr());
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    //begin_write.notify();
    //wait(end_write);
  }
  else if (trans.is_read()){
    cout<<"\t\t[xtea:] Received invocation of the b_transport primitive - read"<<endl;
    // and load it on the payload
    //*((iostruct*) trans.get_data_ptr()) = ioDataStruct;
    xtea_packet = *((iostruct*) trans.get_data_ptr());
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    //begin_read.notify();
    //wait(end_read);
    *((iostruct*) trans.get_data_ptr()) = xtea_packet;
  }

  //t += timing_annotation;

}*/

void xtea_LT_testbench::run()
{

  sc_time local_time = m_qk.get_local_time();

  //iostructR binary_packet;
  iostructV valvola_packet;
  iostructT serbatoio_packet;
  // First transaction (initialization)

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

  //-----------------------CALCOLO THRESHOLD-------------------------------------------

  while(true){

    valvola_packet.flag = flag;
    valvola_packet.threshold = threshold;
    payload_valvola.set_data_ptr((unsigned char*) &valvola_packet);
    payload_valvola.set_write();

    //initiator_socket_valvola->b_transport(payload_valvola, local_time);

    if(payload_valvola.get_response_status() == tlm::TLM_OK_RESPONSE){
    }

    wait(5, SC_MS);

    payload_serbatoio.set_data_ptr((unsigned char*) &serbatoio_packet);
    payload_serbatoio.set_read();
    initiator_socket_serbatoio->b_transport(payload_serbatoio, local_time);
    if(payload_serbatoio.get_response_status() == tlm::TLM_OK_RESPONSE){
      cout << "[TB return:] " << serbatoio_packet.livello_acqua << endl;
      livello_acqua_in=serbatoio_packet.livello_acqua;
    }


    if(livello_acqua_in < 5){
      xtea_packet.n2 = 1.1;
      threshold = threshold * 1.1;
      flag = 1;
    } else if (livello_acqua_in > 8.8){
      xtea_packet.n2 = 0.7;
      threshold = threshold * 0.7;
      flag = 2;
    } else if (livello_acqua_in > 5 && livello_acqua_in < 8.8){
      xtea_packet.n2=1;
      threshold = threshold * 1;
      flag = 0;
    }
    xtea_packet.n1 = threshold;

    // payload_binary.set_data_ptr((unsigned char*) &xtea_packet);
    // payload_binary.set_write();
    // initiator_socket_rtl->b_transport(payload_binary, local_time);
    // payload_binary.set_read();
    // initiator_socket_rtl->b_transport(payload_binary, local_time);
    // if(payload_binary.get_response_status() == tlm::TLM_OK_RESPONSE){
    //   threshold=xtea_packet.result;
    // }

    m_qk.set(local_time);
    if (m_qk.need_sync()) {
      m_qk.sync();
    }

    //cout << "[TB:] threshold: " << xtea_packet.datain_word1 << endl;
    //cout << "[TB:] open/close/idle: " << xtea_packet.datain_word2 << endl;

    xtea_packet.datain_word1 = (uint32_t) (/*xtea_packet.n1*/threshold * 100000.0); /*signalconv.range(63,32)*/ //prima parte threshold convertita //threshold
    xtea_packet.datain_word2 = (uint32_t) (/*xtea_packet.n2*/flag * 100000.0); /*signalconv.range(31,0)*/ //seconda parte threshold convertita //open/close/idle

    //-----------------------ECRYPTION-------------------------------------------

    //cout << "[TB:] The encryption of " /*<< std::hex*/ << xtea_packet.datain_word1 << " and " /*<< std::hex*/ << xtea_packet.datain_word2 << endl;
    //cout << "[TB:] With key " << std::hex << xtea_packet.datain_key0 << xtea_packet.datain_key1 << xtea_packet.datain_key2 << xtea_packet.datain_key3 << "\n";

    payload.set_data_ptr((unsigned char*) &xtea_packet); // set payload data
    payload.set_address(0); // set address, 0 here since we have only 1 target and 1 initiator
    payload.set_write(); // write transaction

    // update the local time variable to send it to the target
    // local_time = m_qk.get_local_time();

    xtea_function();
    cout<<"[TB:] Result is: " /*<< std::hex */<< xtea_packet.result0 << " and " /*<< std::hex*/ << xtea_packet.result1 << endl;

    // start write transaction
    //cout<<"[TB:] Invoking the b_transport primitive - write"<<endl;
    initiator_socket->b_transport(payload, local_time);

    // start read transaction
    // payload.set_read();
    // if(payload.get_response_status() == tlm::TLM_OK_RESPONSE){
    //   cout<<"[TB:] TLM protocol correctly implemented"<<endl;
    // }

    // // temporal decoupling> get time and check if we have to synchronize with the target
    // cout << "Time: " << sc_time_stamp() << " + " << local_time << endl;
    // m_qk.set(local_time);
    // if (m_qk.need_sync()) {
    //   // synchronize simulation time
    //   cout << "SYNCHRONIZING" << endl;
    //   m_qk.sync();
    //   cout << "#####################" << endl;
    // }
  }
  sc_stop();

}

// constructor
xtea_LT_testbench::xtea_LT_testbench(sc_module_name name)
  : sc_module(name)
{

  //initiator_socket_valvola(*this);
  initiator_socket_serbatoio(*this);
  //nitiator_socket_rtl(*this);

  // initialize TLM socket
  initiator_socket(*this);

  // run is a thread
  SC_THREAD(run);

  // set parameters for temporal decoupling
  // one quantum is made of 500 ns
  m_qk.set_global_quantum(sc_time(500, SC_NS));
  m_qk.reset();

}

//-----------------------------xtea---------------------------------------------

void xtea_LT_testbench::xtea_function(){
  //cout<<"\t\t[xtea:] Calculating xtea_function ... Inizio la criptazione: "<<endl;
  //tmp_result = sqrt((float)ioDataStruct.datain);
  sc_uint<32> tmp_result0 = xtea_packet.datain_word1;
  sc_uint<32> tmp_result1 = xtea_packet.datain_word2;
  sc_uint<64> sum = 0;
  sc_uint<32> temp = 0;
  sc_uint<32> delta = 0x9e3779b9;
  sc_uint<32> i;
  //sum = delta*32;

  for (i=0; i<32; i++) {
    if((sum & 3) == 0)
      temp = xtea_packet.datain_key0;
    else if((sum & 3) == 1)
      temp = xtea_packet.datain_key1;
    else if ((sum & 3) == 2)
      temp = xtea_packet.datain_key2;
    else temp = xtea_packet.datain_key3;

    tmp_result0 += (((tmp_result1 << 4) ^ (tmp_result1 >> 5)) + tmp_result1) ^ (sum + temp);

    sum += delta;

    if(((sum>>11) & 3) == 0)
      temp = xtea_packet.datain_key0;
    else if(((sum>>11) & 3) == 1)
      temp = xtea_packet.datain_key1;
    else if (((sum>>11) & 3) == 2)
      temp = xtea_packet.datain_key2;
    else temp = xtea_packet.datain_key3;

    tmp_result1 += (((tmp_result0 << 4) ^ (tmp_result0 >> 5)) + tmp_result0) ^ (sum + temp);

  }
  xtea_packet.result0 = tmp_result0;
  xtea_packet.result1 = tmp_result1;
}

//------------------------------------------------------------------------------
